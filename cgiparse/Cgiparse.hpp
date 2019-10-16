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

    using Getfunction_t = std::function<std::string (const std::string&)>;

    class CgiInputParser {
    public:
        enum class CgiInputTypes {
            MISSING,
            INVALID_ARGUMENT,
            OUT_OF_RANGE
        };

        virtual ~CgiInputParser() = default;

        void GetCgiArgs(cgiparse::Getfunction_t &getter) {
            resetErrors();
            Parse(getter);
        }

        void GetCgiArgs(cgiparse::Getfunction_t &&getter) {
            resetErrors();
            Parse(getter);
        }

        bool HasErrors() {
            return m_errors.size() > 0;
        }

        std::map<std::string, CgiInputTypes> &getErrors() {
            return m_errors;
        }

    protected:
        virtual void Parse(cgiparse::Getfunction_t &getter) = 0;

        template<typename T, typename std::enable_if<std::is_unsigned<T>::value, int>::type = 0>
        void cgiInput(cgiparse::Getfunction_t &getter, T &argument, const std::string key, int base = 10, std::size_t *pos = 0) {
            try {
                auto str = getter(key);
                if (str.size() == 0) {
                    m_errors.emplace(std::make_pair(key, CgiInputTypes::MISSING));
                    return;
                }
                argument = std::stoull(str, pos, base);
            } catch(std::invalid_argument &e) {
                m_errors.emplace(std::make_pair(key, CgiInputTypes::INVALID_ARGUMENT));
            } catch(std::out_of_range &e) {
                m_errors.emplace(std::make_pair(key, CgiInputTypes::OUT_OF_RANGE));
            }
        }

        template<typename T, typename std::enable_if<std::is_signed<T>::value && !std::is_floating_point<T>::value, int>::type = 0>
        void cgiInput(cgiparse::Getfunction_t &getter, T &argument, const std::string key, int base = 10, std::size_t *pos = 0) {
            try {
                auto str = getter(key);
                if (str.size() == 0) {
                    m_errors.emplace(std::make_pair(key, CgiInputTypes::MISSING));
                    return;
                }
                argument = std::stoll(str, pos, base);
            } catch(std::invalid_argument &e) {
                m_errors.emplace(std::make_pair(key, CgiInputTypes::INVALID_ARGUMENT));
            } catch(std::out_of_range &e) {
                m_errors.emplace(std::make_pair(key, CgiInputTypes::OUT_OF_RANGE));
            }
        }

        template<typename T, typename std::enable_if<std::is_floating_point<T>::value, int>::type = 0>
        void cgiInput(cgiparse::Getfunction_t &getter, T &argument, const std::string key, std::size_t *pos = 0) {
            try {
                auto str = getter(key);
                if (str.size() == 0) {
                    m_errors.emplace(std::make_pair(key, CgiInputTypes::MISSING));
                    return;
                }
                argument = std::stold(str, pos);
            } catch(std::invalid_argument &e) {
                m_errors.emplace(std::make_pair(key, CgiInputTypes::INVALID_ARGUMENT));
            } catch(std::out_of_range &e) {
                m_errors.emplace(std::make_pair(key, CgiInputTypes::OUT_OF_RANGE));
            }
        }

        void cgiInput(cgiparse::Getfunction_t &getter, std::string &argument, const std::string key) {
            auto str = getter(key);
            if (str.size() == 0) {
                m_errors.emplace(std::make_pair(key, CgiInputTypes::MISSING));
                return;
            }
            argument = str;
        }

        template<typename T, typename std::enable_if<std::is_unsigned<T>::value, int>::type = 0>
        void cgiInputOptional(cgiparse::Getfunction_t &getter, T &argument, const std::string key, int base = 10, std::size_t *pos = 0) {
            try {
                auto str = getter(key);
                if (str.size() == 0) return;
                argument = std::stoull(str, pos, base);
            } catch(std::invalid_argument &e) {
                m_errors.emplace(std::make_pair(key, CgiInputTypes::INVALID_ARGUMENT));
            } catch(std::out_of_range &e) {
                m_errors.emplace(std::make_pair(key, CgiInputTypes::OUT_OF_RANGE));
            }
        }

        template<typename T, typename std::enable_if<std::is_signed<T>::value && !std::is_floating_point<T>::value, int>::type = 0>
        void cgiInputOptional(cgiparse::Getfunction_t &getter, T &argument, const std::string key, int base = 10, std::size_t *pos = 0) {
            try {
                auto str = getter(key);
                if (str.size() == 0) return;
                argument = std::stoll(str, pos, base);
            } catch(std::invalid_argument &e) {
                m_errors.emplace(std::make_pair(key, CgiInputTypes::INVALID_ARGUMENT));
            } catch(std::out_of_range &e) {
                m_errors.emplace(std::make_pair(key, CgiInputTypes::OUT_OF_RANGE));
            }
        }

        template<typename T, typename std::enable_if<std::is_floating_point<T>::value, int>::type = 0>
        void cgiInputOptional(cgiparse::Getfunction_t &getter, T &argument, const std::string key, std::size_t *pos = 0) {
            try {
                auto str = getter(key);
                if (str.size() == 0) return;
                argument = std::stold(str, pos);
            } catch(std::invalid_argument &e) {
                m_errors.emplace(std::make_pair(key, CgiInputTypes::INVALID_ARGUMENT));
            } catch(std::out_of_range &e) {
                m_errors.emplace(std::make_pair(key, CgiInputTypes::OUT_OF_RANGE));
            }
        }

        void cgiInputOptional(cgiparse::Getfunction_t &getter, std::string &argument, const std::string key) {
            auto str = getter(key);
            if (str.size() == 0) return;
            argument = str;
        }

    private:
        std::map<std::string, CgiInputTypes> m_errors;

        void resetErrors() {
            m_errors.clear();
        }

    };

}

#endif