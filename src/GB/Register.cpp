#include <GB/Register.h>

namespace GB {

std::function<void()> Register::m_on_overflow;
std::function<void()> Register::m_on_zero;

std::function<void()> WideRegister::m_on_overflow;
std::function<void()> WideRegister::m_on_zero;

}
