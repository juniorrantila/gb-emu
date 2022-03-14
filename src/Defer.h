#pragma once

template <typename F>
class Defer {
public:
    Defer(F lambda)
        : m_lambda(lambda)
    {
    }
    ~Defer() { m_lambda(); }
private:
    F m_lambda;
};

