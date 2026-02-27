#ifndef MOS6502_MEMORYBUS_HEADER
#define MOS6502_MEMORYBUS_HEADER

#include <type_traits>
#include <cstdint>
#include <tuple>

namespace libemu::mos6502{

namespace impl{
    template<typename>
    struct member_function_traits;

    template<typename R, typename C, typename... Args>
    struct member_function_traits<R(C::*)(Args...)> {
        using return_type = R;
        using args_tuple  = std::tuple<Args...>;
    };
}

template <class T>
concept memory_bus = requires{
    requires requires {
        typename impl::member_function_traits<decltype(&T::write)>;
        typename impl::member_function_traits<decltype(&T::read)>;
    };
}
&&
[]<class Bus>(){
    using write_traits = impl::member_function_traits<decltype(&Bus::write)>;
    using read_traits  = impl::member_function_traits<decltype(&Bus::read)>;

    using write_args = typename write_traits::args_tuple;
    using read_args  = typename read_traits::args_tuple;

    using addr_type = std::tuple_element_t<0, write_args>;
    using data_type = std::tuple_element_t<1, write_args>;
    using read_addr = std::tuple_element_t<0, read_args>;

    return
        std::is_unsigned_v<addr_type> &&
        std::is_unsigned_v<data_type> &&
        std::is_unsigned_v<read_addr> &&

        sizeof(addr_type) >= sizeof(std::uint16_t) &&
        sizeof(read_addr) >= sizeof(std::uint16_t) &&
        sizeof(data_type) >= sizeof(std::uint8_t)  &&

        std::same_as<typename write_traits::return_type, void> &&
        std::same_as<typename read_traits::return_type, std::uint8_t>;

}.template operator()<T>();

}

#endif