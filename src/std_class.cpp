#include <andy/lang/lang.hpp>

#include <iostream>

#include <andy/lang/interpreter.hpp>
#include <andy/lang/extension.hpp>

std::shared_ptr<andy::lang::structure> andy::lang::std_class::create(andy::lang::interpreter* interpreter)
{
    auto StdClass = std::make_shared<andy::lang::structure>("StdClass");

    StdClass->methods = {
        { "print", andy::lang::method("print", method_storage_type::class_method, {"message"}, [interpreter](std::shared_ptr<andy::lang::object> object, std::vector<std::shared_ptr<andy::lang::object>> params) {
            std::shared_ptr<andy::lang::object> obj = params[0]->cls->methods["to_string"].call(params[0]);
            std::cout << obj->as<std::string>();

            return nullptr;
        })},

        { "puts", andy::lang::method("puts", method_storage_type::class_method, {"message"}, [interpreter](std::shared_ptr<andy::lang::object> object, std::vector<std::shared_ptr<andy::lang::object>> params) {
            std::shared_ptr<andy::lang::object> obj = params[0]->cls->methods["to_string"].call(params[0]);
            std::cout << obj->as<std::string>() << std::endl;

            return nullptr;
        })},

        { "gets", andy::lang::method("gets", method_storage_type::class_method, [interpreter](std::shared_ptr<andy::lang::object> object, std::vector<std::shared_ptr<andy::lang::object>> params) {
            std::string line;
            std::getline(std::cin, line);

            return andy::lang::object::instantiate(interpreter, interpreter->StringClass, std::move(line));
        })},

        { "system", andy::lang::method("system", method_storage_type::class_method, {"command"}, [interpreter](std::shared_ptr<andy::lang::object> object, std::vector<std::shared_ptr<andy::lang::object>> params) {
            std::shared_ptr<andy::lang::object> command = params[0]->cls->methods["to_string"].call(params[0]);
            int code = ((std::system(command->as<std::string>().c_str())) & 0xff00) >> 8;

            return andy::lang::object::instantiate(interpreter, interpreter->IntegerClass, code);
        })},

        { "import", andy::lang::method("import", method_storage_type::class_method, {"module"}, [interpreter](std::shared_ptr<andy::lang::object> object, std::vector<std::shared_ptr<andy::lang::object>> params) {
            std::string module = params[0]->as<std::string>();
            extension::import(interpreter, module);
            return nullptr;
        })},
    };
    
    return StdClass;
}