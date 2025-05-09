#ifndef PRIMITIVE_LIB_HPP_
#define PRIMITIVE_LIB_HPP_

#include "rclcpp/rclcpp.hpp"
#include <string>
#include <functional>
#include <unordered_map>
#include <stdexcept>
#include <utility>

class Primitive {
public:
    virtual bool Excute() = 0;
    virtual void Stop() = 0;

    // 设置参数（类型安全）
    template <typename T>
    bool write_param(const std::string& key, T value) {
        auto it = param_setters_.find(key);
        if (it != param_setters_.end()) {
            auto setter = dynamic_cast<ParamSetter<T>*>(it->second.get());
            if (setter) {
                setter->set(value);
                return true;
            }
        }
        return false;
    }

    // 获取参数（类型安全）
    template <typename T>
    T result(const std::string& key) const {
        auto it = param_getters_.find(key);
        if (it != param_getters_.end()) {
            auto getter = dynamic_cast<ParamGetter<T>*>(it->second.get());
            if (getter) {
                return getter->get();
            }
        }
        throw std::runtime_error("Invalid key or type: " + key);
    }

protected:
    // 参数操作基类
    struct ParamSetterBase {
        virtual ~ParamSetterBase() = default;
    };

    struct ParamGetterBase {
        virtual ~ParamGetterBase() = default;
    };

    // 类型特化的参数操作
    template <typename T>
    struct ParamSetter : ParamSetterBase {
        std::function<void(T)> set_func;
        explicit ParamSetter(std::function<void(T)> func) : set_func(std::move(func)) {}
        void set(T value) { set_func(value); }
    };

    template <typename T>
    struct ParamGetter : ParamGetterBase {
        std::function<T()> get_func;
        explicit ParamGetter(std::function<T()> func) : get_func(std::move(func)) {}
        T get() { return get_func(); }
    };

    // 注册参数的宏（提升可读性）
    #define REGISTER_PARAM(KEY, TYPE, VAR) \
        param_setters_[KEY] = std::make_unique<ParamSetter<TYPE>>( \
            [this](TYPE value) { VAR = value; }); \
        param_getters_[KEY] = std::make_unique<ParamGetter<TYPE>>( \
            [this]() { return VAR; });

    std::unordered_map<std::string, std::unique_ptr<ParamSetterBase>> param_setters_;
    std::unordered_map<std::string, std::unique_ptr<ParamGetterBase>> param_getters_;
    
};











#endif // PRIMITIVE_LIB_HPP_