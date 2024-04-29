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
        if (uri.string() == "https://json-schema.org/draft/2019-09/schema") 
        {
            //JSONCONS_THROW(jsonschema::schema_error(std::string("Don't currently support ") + "https://json-schema.org/draft/2019-09/schema"));
            return jsoncons::jsonschema::draft201909::schema_draft201909<json>::get_schema();
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
                    jsonschema::evaluation_options{}.default_version(jsonschema::schema::draft201909()));

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
 
TEST_CASE("jsonschema draft2019-09 tests")
{
    SECTION("issues")
    {
        //jsonschema_tests("./jsonschema/issues/draft2019-09/issue-anchor.json");
        //jsonschema_tests("./jsonschema/issues/draft2019-09/issue-not.json");
        //jsonschema_tests("./jsonschema/issues/draft2019-09/issue-unevaluatedProperties.json");
        //jsonschema_tests("./jsonschema/issues/draft2019-09/issue-ref.json");
        //jsonschema_tests("./jsonschema/issues/draft2019-09/issue-recursiveRef.json");
    }
    SECTION("tests")
    {

        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/anchor.json"); // UNCOMMENT METASCHEMA
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/additionalItems.json");
#ifdef JSONCONS_HAS_STD_REGEX
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/additionalProperties.json");
#endif

        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/allOf.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/anyOf.json");

        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/boolean_schema.json");

        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/const.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/contains.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/default.json");

        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/defs.json");  // METASCHEMA

        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/enum.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/exclusiveMaximum.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/exclusiveMinimum.json");

#ifdef JSONCONS_HAS_STD_REGEX
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/format.json");
#endif

        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/if-then-else.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/items.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/maximum.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/maxItems.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/maxLength.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/maxProperties.json");

        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/minimum.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/minItems.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/minLength.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/minProperties.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/multipleOf.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/not.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/oneOf.json");

        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/recursiveRef.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/unevaluatedProperties.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/unevaluatedItems.json");

#ifdef JSONCONS_HAS_STD_REGEX
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/pattern.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/patternProperties.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/properties.json");
#endif
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/propertyNames.json");

        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/ref.json"); 

        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/refRemote.json");

        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/required.json");

        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/type.json");

        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/uniqueItems.json"); 
/*      // format tests
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/optional/format/date.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/optional/format/date-time.json");
        //jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/optional/format/ecmascript-regex.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/optional/format/email.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/optional/format/hostname.json");
        //jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/optional/format/idn-email.json");
        //jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/optional/format/idn-hostname.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/optional/format/ipv4.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/optional/format/ipv6.json");
        //jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/optional/format/iri.json");
        //jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/optional/format/iri-reference.json");
        //jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/optional/format/json-pointer.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/optional/format/regex.json");
        //jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/optional/format/relative-json-pointer.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/optional/format/time.json");
 
        //jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/optional/format/uri.json");
        //jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/optional/format/uri-reference.json");
        //jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2019-09/optional/format/uri-template.json");
*/
    }
}
