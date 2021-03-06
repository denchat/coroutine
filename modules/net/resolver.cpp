// ---------------------------------------------------------------------------
//
//  Author  : github.com/luncliff (luncliff@gmail.com)
//  License : CC BY 4.0
//
// ---------------------------------------------------------------------------
#include <coroutine/net.h>
#include <gsl/gsl>

using namespace std;
using namespace coro;

array<char, NI_MAXHOST> hnbuf{};

auto host_name() noexcept -> czstring_host {
    const auto namelen = gsl::narrow_cast<socklen_t>(hnbuf.size());
    ::gethostname(hnbuf.data(), namelen);
    return hnbuf.data();
}

GSL_SUPPRESS(type .1)
int get_name(const endpoint_t& ep, //
             zstring_host name, zstring_serv serv) noexcept {

    socklen_t slen = NI_MAXSERV;
    if (serv == nullptr)
        slen = 0;

    socklen_t addrlen = 0;
    if (ep.storage.ss_family == AF_INET)
        addrlen = sizeof(ep.in4);
    else if (ep.storage.ss_family == AF_INET6)
        addrlen = sizeof(ep.in6);

    // available flags...
    //      NI_NAMEREQD
    //      NI_DGRAM
    //      NI_NOFQDN
    //      NI_NUMERICHOST
    //      NI_NUMERICSERV
    // non-zero if failed
    return ::getnameinfo(addressof(ep.addr), addrlen, name, NI_MAXHOST, serv,
                         slen, NI_NUMERICHOST | NI_NUMERICSERV);
}

GSL_SUPPRESS(es .76)
GSL_SUPPRESS(type .1)
GSL_SUPPRESS(gsl.util)
auto resolve(const addrinfo& hint, //
             czstring_host name, czstring_serv serv) noexcept
    -> coro::enumerable<endpoint_t> {

    addrinfo* list = nullptr;
    if (::getaddrinfo(name, serv, addressof(hint), &list))
        co_return;

    // RAII clean up for the assigned addrinfo
    // This holder guarantees clean up
    //      when the generator is destroyed
    auto d1 = gsl::finally([list]() noexcept { ::freeaddrinfo(list); });

    endpoint_t* ptr = nullptr;
    for (addrinfo* it = list; it != nullptr; it = it->ai_next) {
        ptr = reinterpret_cast<endpoint_t*>(it->ai_addr);

        endpoint_t& ep = *ptr;
        co_yield ep;
    }
}
