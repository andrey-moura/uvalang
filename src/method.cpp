#include <andy/lang/method.hpp>
#include <andy/lang/object.hpp>
#include <andy/lang/class.hpp>

std::shared_ptr<andy::lang::object> andy::lang::method::call(std::shared_ptr<andy::lang::object> o)
{
    return function(o, std::vector<std::shared_ptr<andy::lang::object>>(), std::map<std::string, std::shared_ptr<andy::lang::object>>());
}

void andy::lang::method::init_params(std::vector<std::string> __params)
{
    for(auto& param : __params) {
        fn_parameter fn_param(std::move(param));
        if(fn_param.named) {
            named_params.push_back(std::move(fn_param));
        } else {
            positional_params.push_back(std::move(fn_param));
        }
    }
}
