#pragma once

#include <cassert>
#include <unordered_map>

#include "peer_addr_wrapper.h"

namespace mpeers
{

	template<typename peer_addr, typename peer_factory, typename peer_type>
	class context
	{
	public:
		context(peer_factory& factory) : m_peer_factory(factory) {}
		void input(const char *data, size_t size, ::std::shared_ptr<peer_addr> addr)
		{
			auto it = m_peers.find(addr);
			peer_type *peer = NULL;
			if (it != m_peers.end())
			{
				peer = it->second;
			}
			else
			{
				peer = m_peer_factory.create(addr);
				if (peer == NULL) return;
				m_peers[addr] = peer;
			}
			peer->input(data, size);
		}
		void close_peer(::std::shared_ptr<peer_addr> addr)
		{
			auto it = m_peers.find(addr);
			assert(it != m_peers.end());
			m_peer_factory.close_peer(it->second);
			m_peers.erase(it);
		}
	private:
		peer_factory& m_peer_factory;
		::std::unordered_map<peer_addr_wrapper<peer_addr>, peer_type*> m_peers;
	};

}
