#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <iostream>
#include <iomanip>
#include <doctest/doctest.h>
#include "student_serializer.hpp"

#include <cstring>
#include <cstdint>
#include <stdexcept>

// ─────────────────────────────────────────────────────────────────────────────
// Helpers
// ─────────────────────────────────────────────────────────────────────────────
namespace {

template <typename T>
T read(const std::vector<char>& buf, std::size_t offset)
{
    T data;
    std::memcpy(&data, buf.data() + offset, sizeof(T));

    return data;
}

} // namespace


// ═════════════════════════════════════════════════════════════════════════════
// serialize()
// ═════════════════════════════════════════════════════════════════════════════
TEST_SUITE("StudentSerializer::serialize") {

    // ── buffer size ──────────────────────────────────────────────────────────

    TEST_CASE("total buffer size is 4 + total_size bytes")
    {
        StudentRec rec{1, "Ana", 9.5f};
        auto buf = StudentSerializer::serialize(rec);

        // 4 (total_size header) + 4 (id) + 3 (name) + 4 (nota) = 15
        CHECK(buf.size() == 15u);
    }

    TEST_CASE("buffer size is correct for an empty name")
    {
        StudentRec rec{2, "", 7.0f};
        auto buf = StudentSerializer::serialize(rec);

        // 4 + 4 (id) + 0 (name) + 4 (nota) = 12
        CHECK(buf.size() == 12u);
    }

    TEST_CASE("buffer size scales with name length")
    {
        StudentRec rec{3, "Carlos Eduardo", 8.0f}; // name = 14 chars
        auto buf = StudentSerializer::serialize(rec);

        // 4 + 4 + 14 + 4 = 26
        CHECK(buf.size() == 26u);
    }

    // ── total_size field value ────────────────────────────────────────────────

    TEST_CASE("total_size field equals id + name_len + nota (8 + name.size())")
    {
        StudentRec rec{10, "Maria", 6.75f}; // name = 5 chars
        auto buf = StudentSerializer::serialize(rec);

        REQUIRE(buf.size() >= 4);

        const uint32_t stored_total = read<uint32_t>(buf, 0);
        CHECK(stored_total == 4u + 5u + 4u); // 13
    }

    TEST_CASE("total_size field is 8 when name is empty")
    {
        StudentRec rec{99, "", 10.0f};
        auto buf = StudentSerializer::serialize(rec);
        REQUIRE(buf.size() >= 4);

        CHECK(read<uint32_t>(buf, 0) == 8u);
    }

    // ── field values in the buffer ────────────────────────────────────────────

    TEST_CASE("id is written at byte offset 4")
    {
        StudentRec rec{42, "Luis", 5.5f};
        auto buf = StudentSerializer::serialize(rec);

        CHECK(read<uint32_t>(buf, 4) == 42u);
    }

    TEST_CASE("name bytes start at offset 8 and match the original string")
    {
        const std::string name = "Pedro";
        StudentRec rec{7, name, 8.0f};
        auto buf = StudentSerializer::serialize(rec);

        const std::string extracted(buf.data() + 8, name.size());
        CHECK(extracted == name);
    }

    TEST_CASE("nota is written immediately after the name bytes")
    {
        const std::string name = "Sofia"; // 5 chars → nota at offset 8+5=13
        StudentRec rec{5, name, 7.25f};
        auto buf = StudentSerializer::serialize(rec);

        CHECK(read<float>(buf, 8 + name.size()) == doctest::Approx(7.25f));
    }

    TEST_CASE("nota is written at offset 8 when name is empty")
    {
        StudentRec rec{1, "", 9.0f};
        auto buf = StudentSerializer::serialize(rec);

        CHECK(read<float>(buf, 8) == doctest::Approx(9.0f));
    }

    // ── edge values ───────────────────────────────────────────────────────────

    TEST_CASE("id of 0 is serialized correctly")
    {
        StudentRec rec{0, "Zero", 1.0f};
        auto buf = StudentSerializer::serialize(rec);

        CHECK(read<uint32_t>(buf, 4) == 0u);
    }

    TEST_CASE("maximum uint32_t id is serialized correctly")
    {
        StudentRec rec{UINT32_MAX, "Max", 10.0f};
        auto buf = StudentSerializer::serialize(rec);

        CHECK(read<uint32_t>(buf, 4) == UINT32_MAX);
    }

    TEST_CASE("nota of 0.0f is serialized correctly")
    {
        StudentRec rec{1, "Zero", 0.0f};
        auto buf = StudentSerializer::serialize(rec);

        CHECK(read<float>(buf, 8 + 4 /*"Zero"*/) == doctest::Approx(0.0f));
    }

    TEST_CASE("name with spaces is serialized correctly")
    {
        const std::string name = "Jose Antonio";
        StudentRec rec{8, name, 8.5f};
        auto buf = StudentSerializer::serialize(rec);

        const std::string extracted(buf.data() + 8, name.size());
        CHECK(extracted == name);
    }
}


// ═════════════════════════════════════════════════════════════════════════════
// deserialize()
// ═════════════════════════════════════════════════════════════════════════════
TEST_SUITE("StudentSerializer::deserialize") {

    // ── field recovery ────────────────────────────────────────────────────────

    TEST_CASE("id is recovered correctly")
    {
        // auto buf = build_raw(123, "Elena", 9.0f);
        std::vector<char> buf ({
            0x0D, 0x00, 0x00, 0x00,
            0x7B, 0x00, 0x00, 0x00,
            0x45, 0x6C, 0x65, 0x6E, 0x61,
            0x00, 0x00, 0x10, 0x41,
        });

        auto rec = StudentSerializer::deserialize(buf);
        CHECK(rec.id == 123u);
    }

    TEST_CASE("name is recovered correctly")
    {
        // auto buf = build_raw(1, "Roberto", 7.5f);
        std::vector<char> buf({ '\x0F', '\x00', '\x00', '\x00',
                                '\x01', '\x00', '\x00', '\x00',
                                '\x52', '\x6F', '\x62', '\x65', '\x72', '\x74', '\x6F',
                                '\x00', '\x00', '\xF0', '\x40',});

        auto rec = StudentSerializer::deserialize(buf);
        CHECK(rec.name == "Roberto");
    }

    TEST_CASE("nota is recovered correctly")
    {
        // auto buf = build_raw(1, "Lucia", 6.25f);
        std::vector<char> buf ({ '\x0D', '\x00', '\x00', '\x00',
                                 '\x01', '\x00', '\x00', '\x00',
                                 '\x4C', '\x75', '\x63', '\x69', '\x61',
                                 '\x00', '\x00', '\xC8', '\x40',});

        auto rec = StudentSerializer::deserialize(buf);

        CHECK(rec.nota == doctest::Approx(6.25f));
    }

    TEST_CASE("empty name is recovered correctly")
    {
        // auto buf = build_raw(5, "", 8.0f);
        std::vector<char> buf ({
            0x08, 0x00, 0x00, 0x00,
            0x05, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x41,
        });

        auto rec = StudentSerializer::deserialize(buf);

        CHECK(rec.id   == 5u);
        CHECK(rec.name == "");
        CHECK(rec.nota == doctest::Approx(8.0f));
    }

    TEST_CASE("name with spaces is recovered correctly")
    {
        // auto buf = build_raw(9, "Ana Maria", 9.75f);
        std::vector<char> buf ({
           0x11, 0x00, 0x00, 0x00,
           0x09, 0x00, 0x00, 0x00,
           0x41, 0x6E, 0x61, 0x20, 0x4D, 0x61, 0x72, 0x69, 0x61,
           0x00, 0x00, 0x1C, 0x41,
        });
        auto rec = StudentSerializer::deserialize(buf);

        CHECK(rec.name == "Ana Maria");
    }

    // ── roundtrip ─────────────────────────────────────────────────────────────

    TEST_CASE("serialize → deserialize produces an identical record (typical)")
    {
        StudentRec original{42, "Carlos", 8.5f};
        auto buf     = StudentSerializer::serialize(original);
        auto decoded = StudentSerializer::deserialize(buf);

        CHECK(decoded.id   == original.id);
        CHECK(decoded.name == original.name);
        CHECK(decoded.nota == doctest::Approx(original.nota));
    }

    TEST_CASE("serialize → deserialize roundtrip with empty name")
    {
        StudentRec original{0, "", 0.0f};
        auto buf     = StudentSerializer::serialize(original);
        auto decoded = StudentSerializer::deserialize(buf);

        CHECK(decoded.id   == original.id);
        CHECK(decoded.name == original.name);
        CHECK(decoded.nota == doctest::Approx(original.nota));
    }

    TEST_CASE("serialize → deserialize roundtrip with long name")
    {
        StudentRec original{999, "Maximiliano Alejandro García López", 5.0f};
        auto buf     = StudentSerializer::serialize(original);
        auto decoded = StudentSerializer::deserialize(buf);

        CHECK(decoded.id   == original.id);
        CHECK(decoded.name == original.name);
        CHECK(decoded.nota == doctest::Approx(original.nota));
    }

    TEST_CASE("serialize → deserialize roundtrip with max uint32 id")
    {
        StudentRec original{UINT32_MAX, "Max", 10.0f};
        auto buf     = StudentSerializer::serialize(original);
        auto decoded = StudentSerializer::deserialize(buf);

        CHECK(decoded.id == UINT32_MAX);
    }

    // ── malformed input ───────────────────────────────────────────────────────

    TEST_CASE("throws on completely empty buffer")
    {
        std::vector<char> buf{};
        CHECK_THROWS_AS(StudentSerializer::deserialize(buf), std::runtime_error);
    }

    TEST_CASE("throws when buffer is shorter than the total_size header (1-3 bytes)")
    {
        std::vector<char> buf(3, '\0');
        CHECK_THROWS_AS(StudentSerializer::deserialize(buf), std::runtime_error);
    }

    TEST_CASE("throws when total_size claims more bytes than the buffer holds")
    {
        // total_size = 100 but we only provide 12 bytes total
        std::vector<char> buf(12, '\0');
        const uint32_t bogus_total = 100u;
        std::memcpy(buf.data(), &bogus_total, 4);
        CHECK_THROWS_AS(StudentSerializer::deserialize(buf), std::runtime_error);
    }

    TEST_CASE("throws when total_size is less than the minimum value of 8")
    {
        // total_size = 7 → cannot hold id(4) + nota(4)
        std::vector<char> buf(7, '\0');
        CHECK_THROWS_AS(StudentSerializer::deserialize(buf), std::runtime_error);
    }
}
