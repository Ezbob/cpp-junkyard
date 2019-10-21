#ifndef CGIPARSE_H_adkasdlkasdaooiwe230123fec
#define CGIPARSE_H_adkasdlkasdaooiwe230123fec

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <functional>
#include <map>

namespace cgiparse {

    using Getter_t = std::function<std::string (const std::string&)>;

    enum class CgiInputErrorTypes {
        OK = 0,
        MISSING,
        INVALID_ARGUMENT,
        OUT_OF_RANGE
    };

    struct DefaultDeserializer {

        template<typename T, typename std::enable_if<std::is_signed<T>::value && !std::is_floating_point<T>::value, int>::type = 0>
        CgiInputErrorTypes deserialize(T &value, const std::string &input, int base = 10, std::size_t *pos = 0) {
            try {
                if (input.size() == 0) return CgiInputErrorTypes::MISSING;
                value = std::stoll(input, pos, base);
            } catch(const std::invalid_argument &e) {
                return CgiInputErrorTypes::INVALID_ARGUMENT;
            } catch(const std::out_of_range &e) {
                return CgiInputErrorTypes::OUT_OF_RANGE;
            }

            return CgiInputErrorTypes::OK;
        }

        template<typename T, typename std::enable_if<std::is_unsigned<T>::value, int>::type = 0>
        CgiInputErrorTypes deserialize(T &value, const std::string &input, int base = 10, std::size_t *pos = 0) {
            try {
                if (input.size() == 0) return CgiInputErrorTypes::MISSING;
                value = std::stoull(input, pos, base);
            } catch(const std::invalid_argument &e) {
                return CgiInputErrorTypes::INVALID_ARGUMENT;
            } catch(const std::out_of_range &e) {
                return CgiInputErrorTypes::OUT_OF_RANGE;
            }

            return CgiInputErrorTypes::OK;
        }

        template<typename T, typename std::enable_if<std::is_floating_point<T>::value, int>::type = 0>
        CgiInputErrorTypes deserialize(T &value, const std::string &input, std::size_t *pos = 0) {
            try {
                if (input.size() == 0) return CgiInputErrorTypes::MISSING;
                value = std::stold(input, pos);
            } catch(const std::invalid_argument &e) {
                return CgiInputErrorTypes::INVALID_ARGUMENT;
            } catch(const std::out_of_range &e) {
                return CgiInputErrorTypes::OUT_OF_RANGE;
            }

            return CgiInputErrorTypes::OK;
        }

        CgiInputErrorTypes deserialize(std::string &value, const std::string &input, bool optional = false) {
            if (input.size() == 0 && !optional) return CgiInputErrorTypes::MISSING;
            value = input;
            return CgiInputErrorTypes::OK;
        }
    };

    template<typename Deserializer_T = DefaultDeserializer>
    class CgiInputParser {

    public:
        virtual ~CgiInputParser() = default;

        void GetCgiArgs(cgiparse::Getter_t &getter) {
            resetErrors();
            Parse(getter);
        }

        void GetCgiArgs(cgiparse::Getter_t &&getter) {
            resetErrors();
            Parse(getter);
        }

        bool HasErrors() {
            return m_errors.size() > 0;
        }

        std::map<std::string, CgiInputErrorTypes> &getErrors() {
            return m_errors;
        }

    protected:
        virtual void Parse(cgiparse::Getter_t &getter) = 0;

        template<typename T, typename std::enable_if<!std::is_floating_point<T>::value, int>::type = 0>
        void cgiInput(cgiparse::Getter_t &getter, T &argument, const std::string key, int base = 10, std::size_t *pos = 0) {
            auto str = getter(key);
            CgiInputErrorTypes result = m_deserializer.deserialize(argument, str, base, pos);
            if (result != CgiInputErrorTypes::OK) {
                m_errors.emplace(std::make_pair(key, result));
            }
        }

        template<typename T, typename std::enable_if<std::is_floating_point<T>::value, int>::type = 0>
        void cgiInput(cgiparse::Getter_t &getter, T &argument, const std::string key, std::size_t *pos = 0) {
            auto str = getter(key);
            CgiInputErrorTypes result = m_deserializer.deserialize(argument, str, pos);
            if (result != CgiInputErrorTypes::OK) {
                m_errors.emplace(std::make_pair(key, result));
            }
        }

        void cgiInput(cgiparse::Getter_t &getter, std::string &argument, const std::string key) {
            auto str = getter(key);
            CgiInputErrorTypes result = m_deserializer.deserialize(argument, str);
            if (result != CgiInputErrorTypes::OK) {
                m_errors.emplace(std::make_pair(key, result));
            }
        }

        template<typename T, typename std::enable_if<!std::is_floating_point<T>::value, int>::type = 0>
        void cgiInputOptional(cgiparse::Getter_t &getter, T &argument, const std::string key, int base = 10, std::size_t *pos = 0) {
            auto str = getter(key);
            CgiInputErrorTypes result = m_deserializer.deserialize(argument, str, base, pos);
            if (result != CgiInputErrorTypes::OK && result != CgiInputErrorTypes::MISSING) {
                m_errors.emplace(std::make_pair(key, result));
            }
        }

        template<typename T, typename std::enable_if<std::is_floating_point<T>::value, int>::type = 0>
        void cgiInputOptional(cgiparse::Getter_t &getter, T &argument, const std::string key, std::size_t *pos = 0) {
            auto str = getter(key);
            CgiInputErrorTypes result = m_deserializer.deserialize(argument, str, pos);
            if (result != CgiInputErrorTypes::OK && result != CgiInputErrorTypes::MISSING) {
                m_errors.emplace(std::make_pair(key, result));
            }
        }

        void cgiInputOptional(cgiparse::Getter_t &getter, std::string &argument, const std::string key) {
            auto str = getter(key);
            CgiInputErrorTypes result = m_deserializer.deserialize(argument, str);
            if (result != CgiInputErrorTypes::OK && result != CgiInputErrorTypes::MISSING) {
                m_errors.emplace(std::make_pair(key, result));
            }
        }

    private:
        Deserializer_T m_deserializer;
        std::map<std::string, CgiInputErrorTypes> m_errors;

        void resetErrors() {
            m_errors.clear();
        }
    };

}

#endif