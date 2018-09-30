#pragma once

#include <memory>

namespace mpeers
{

	template<typename peer_addr>
	class peer_addr_wrapper
	{
	public:
		typedef ::std::shared_ptr<peer_addr> addr_ptr;
		peer_addr_wrapper(addr_ptr addr) : m_addr(addr) {};
		const addr_ptr& addr() const { return m_addr; }
		bool operator==(const peer_addr_wrapper& another) const
		{
			return *m_addr == *another.m_addr;
		}
	private:
		addr_ptr m_addr;
	};

}

namespace std
{

	template<typename peer_addr>class hash<::mpeers::peer_addr_wrapper<peer_addr> >
	{
	public:
		size_t operator()(const ::mpeers::peer_addr_wrapper<peer_addr>& addr_wrapper) const
		{
			return addr_wrapper.addr()->hash();
		}
	};

}
