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
        if (uri.string() == "https://json-schema.org/draft/2020-12/schema") 
        {
            //JSONCONS_THROW(jsonschema::schema_error(std::string("Don't currently support ") + "https://json-schema.org/draft/2020-12/schema"));
            return jsoncons::jsonschema::draft202012::schema_draft202012<json>::get_schema();
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
                    jsonschema::evaluation_options{}.default_version(jsonschema::schema::draft202012()));

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
 
TEST_CASE("jsonschema draft2020-12 tests")
{
    SECTION("issues")
    {
        //jsonschema_tests("./jsonschema/issues/draft2020-12/issue-ref.json");
        //jsonschema_tests("./jsonschema/issues/draft2020-12/issue-items.json");
        //jsonschema_tests("./jsonschema/issues/draft2020-12/issue-dynamicRef.json");
        //jsonschema_tests("./jsonschema/issues/draft2020-12/issue-unevaluatedProperties.json");
        //jsonschema_tests("./jsonschema/issues/draft2020-12/issue-unevaluatedItems.json");
    }
//#if 0
    SECTION("tests")
    {

        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2020-12/anchor.json"); 
#ifdef JSONCONS_HAS_STD_REGEX
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2020-12/additionalProperties.json");
#endif
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2020-12/allOf.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2020-12/anyOf.json");

        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2020-12/boolean_schema.json");

        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2020-12/const.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2020-12/contains.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2020-12/default.json");

        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2020-12/defs.json");  
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2020-12/dynamicRef.json");

        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2020-12/enum.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2020-12/exclusiveMaximum.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2020-12/exclusiveMinimum.json");

#ifdef JSONCONS_HAS_STD_REGEX
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2020-12/format.json");
#endif

        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2020-12/if-then-else.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2020-12/items.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2020-12/maximum.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2020-12/maxItems.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2020-12/maxLength.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2020-12/maxProperties.json");

        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2020-12/minimum.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2020-12/minItems.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2020-12/minLength.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2020-12/minProperties.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2020-12/multipleOf.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2020-12/not.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2020-12/oneOf.json");
#ifdef JSONCONS_HAS_STD_REGEX
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2020-12/pattern.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2020-12/patternProperties.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2020-12/properties.json");
#endif
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2020-12/propertyNames.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2020-12/ref.json"); 

        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2020-12/unevaluatedProperties.json");
        
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2020-12/unevaluatedItems.json");

        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2020-12/refRemote.json");

        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2020-12/required.json");

        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2020-12/type.json");

        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2020-12/uniqueItems.json"); 
/*
        // format tests
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2020-12/optional/format/date.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2020-12/optional/format/date-time.json");
        //jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2020-12/optional/format/ecmascript-regex.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2020-12/optional/format/email.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2020-12/optional/format/hostname.json");
        //jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2020-12/optional/format/idn-email.json");
        //jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2020-12/optional/format/idn-hostname.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2020-12/optional/format/ipv4.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2020-12/optional/format/ipv6.json");
        //jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2020-12/optional/format/iri.json");
        //jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2020-12/optional/format/iri-reference.json");
        //jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2020-12/optional/format/json-pointer.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2020-12/optional/format/regex.json");
        //jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2020-12/optional/format/relative-json-pointer.json");
        jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2020-12/optional/format/time.json");
 
        //jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2020-12/optional/format/uri.json");
        //jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2020-12/optional/format/uri-reference.json");
        //jsonschema_tests("./jsonschema/JSON-Schema-Test-Suite/tests/draft2020-12/optional/format/uri-template.json");
*/
    }
//#endif
}
