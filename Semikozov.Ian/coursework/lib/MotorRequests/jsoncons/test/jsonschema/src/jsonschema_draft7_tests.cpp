// Copyright 2013-2024 Daniel Parker
// Distributed under the Boost license, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// See https://github.com/danielaparker/jsoncons for latest version

#include <catch/catch.hpp>
#include <fstream>
#include <iostream>
#include <regex>
#include <jsoncons_ext/jsonschema/jsonschema.hpp>
#include <jsoncons/byte_string.hpp>

using jsoncons::json;
namespace jsonschema = jsoncons::jsonschema;

namespace {

    json resolver(const jsoncons::uri& uri)
    {
        if (uri.path() == "/draft-07/schema") 
        {
            return jsoncons::jsonschema::draft7::schema_draft7<json>::get_schema();
        }
        else
        {
            //std::cout << uri.string() << ", " << uri.path() << "\n";
            std::string pathname = "./jsonschema/JSON-Schema-Test-Suite/remotes";
            pathname += std::string(uri.path());

            std::fstream is(pathname.c_str());
            if (!is)
                throw jsonschema::schema_error("Could not open " + pathname + " for schema loading\n");

            return json::parse(is);
        }
    }

    void jsonschema_tests(const std::string& fpath)
    {
        std::fstream is(fpath);
        if (!is)
        {
            std::cout << "Cannot open file: " << fpath << "\n";
            return;
        }

        json tests = json::parse(is); 
        //std::cout << pretty_print(tests) << "\n";

        int count = 0;
        for (const auto& test_group : tests.array_range()) 
        {
            ++count;
            try
            {
                jsonschema::json_schema<json> compiled = jsonschema::make_json_schema(test_group.at("schema"), resolver, 
                    jsonschema::evaluation_options{}.default_version(jsonschema::schema::draft07())
                    .require_format_validation(true));

                int count_test = 0;
                for (const auto& test_case : test_group["tests"].array_range()) 
                {
                    //std::cout << "  Test case " << count << "." << count_test << ": " << test_case["description"] << "\n";
                    ++count_test;
                    std::size_t errors = 0;
                    auto reporter = [&](const jsonschema::validation_message& o)
                    {
                        ++errors;
                        CHECK_FALSE(test_case["valid"].as<bool>());
                        if (test_case["valid"].as<bool>())
                        {
                            std::cout << "  File: " << fpath << "\n";
                            std::cout << "  Test case " << count << "." << count_test << ": " << test_case["description"] << "\n";
                            std::cout << "  Failed: " << o.instance_location().string() << ": " << o.message() << "\n";
                            for (const auto& err : o.details())
                            {
                                std::cout << "  Nested error: " << err.instance_location().string() << ": " << err.message() << "\n";
                            }
                        }
                    };
                    compiled.validate(test_case.at("data"), reporter);
                    if (errors == 0)
                    {
                        CHECK(test_case["valid"].as<bool>());
                        if (!test_case["valid"].as<bool>())
                        {
                            std::cout << "  File: " << fpath << "\n";
                            std::cout << "  Test case " << count << "." << count_test << ": " << test_case["description"] << "\n";
                        }
                    }
                }
            }
            catch (const std::exception& e)
            {
                std::cout << "  File: " << fpath << " " << count << "\n";
                std::cout << e.what() << "\n\n";
                CHECK(false);
            }
        }
    }
}
 
TEST_CASE("jsonschema draft7 tests")
{
    SECTION("issues")
    {
        //jsonschema_tests("./jsonschema/issues/draft7/issue-content.json");
    }
    SECTION("tests")
    {
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft7/additionalItems.json");
#ifdef JSONCONS_HAS_STD_REGEX
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft7/additionalProperties.json");
#endif
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft7/allOf.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft7/anyOf.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft7/boolean_schema.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft7/const.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft7/contains.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft7/default.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft7/definitions.json"); 

        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft7/dependencies.json");

        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft7/enum.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft7/exclusiveMaximum.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft7/exclusiveMinimum.json");

#ifdef JSONCONS_HAS_STD_REGEX
        //jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft7/format.json");
#endif
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft7/if-then-else.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft7/items.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft7/maximum.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft7/maxItems.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft7/maxLength.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft7/maxProperties.json");

        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft7/minimum.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft7/minItems.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft7/minLength.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft7/minProperties.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft7/multipleOf.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft7/not.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft7/oneOf.json");
#ifdef JSONCONS_HAS_STD_REGEX
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft7/pattern.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft7/patternProperties.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft7/properties.json");
#endif
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft7/propertyNames.json");

        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft7/ref.json"); // *

        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft7/refRemote.json");

        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft7/required.json");

        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft7/type.json");

        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft7/uniqueItems.json"); 
        // format tests
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft7/optional/format/date.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft7/optional/format/date-time.json"); 
        //jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft7/optional/format/ecmascript-regex.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft7/optional/format/email.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft7/optional/format/hostname.json");
        //jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft7/optional/format/idn-email.json");
        //jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft7/optional/format/idn-hostname.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft7/optional/format/ipv4.json"); 
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft7/optional/format/ipv6.json");
        //jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft7/optional/format/iri.json");
        //jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft7/optional/format/iri-reference.json");
        //jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft7/optional/format/json-pointer.json");
        //jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft7/optional/format/regex.json");
        //jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft7/optional/format/relative-json-pointer.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft7/optional/format/time.json"); 
 
        //jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft7/optional/format/uri.json");
        //jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft7/optional/format/uri-reference.json");
        //jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft7/optional/format/uri-template.json");

        //jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft7/optional/content.json"); // REVISIT
    }
    SECTION("#417")
    {
        jsoncons::json schema = jsoncons::json::parse(R"(
    {
      "$id": "https://example.com/polygon",
      "$schema": "http://json-schema.org/draft-07/schema#",
      "unknown-keyword": {
        "point": {
          "type": "object",
          "properties": {
            "x": { "type": "number" },
            "y": { "type": "number" }
          },
          "additionalProperties": false,
          "required": [ "x", "y" ]
        }
      },
      "type": "array",
      "items": { "$ref": "#/unknown-keyword/point" },
      "minItems": 3,
      "maxItems": 1
    }
 )");

            jsoncons::json instance = jsoncons::json::parse(R"(
    [
      {
        "x": 2.5,
        "y": 1.3
      },
      {
        "x": 1,
        "z": 6.7
      }
    ]
 )");

        jsonschema::json_schema<json> compiled = jsoncons::jsonschema::make_json_schema(schema);

        CHECK_FALSE(compiled.is_valid(instance));
    }
}
