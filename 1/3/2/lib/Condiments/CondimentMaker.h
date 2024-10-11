#pragma once

template <typename Condiment, typename... Args>
auto MakeCondiment(const Args&...args)
{
    // Возвращаем функцию, декорирующую напиток, переданный ей в качестве аргумента
    // Дополнительные аргументы декоратора, захваченные лямбда-функцией, передаются
    // конструктору декоратора через make_unique
    return [=](auto && b) {
        // Функции make_unique передаем b вместе со списком аргументов внешней функции
        return make_unique<Condiment>(forward<decltype(b)>(b), args...);
    };
}

template <typename Component, typename Decorator>
auto operator << (Component && component, const Decorator & decorate)
{
    return decorate(forward<Component>(component));
}