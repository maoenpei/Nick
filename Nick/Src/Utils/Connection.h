#pragma once

#include <set>
#include <memory>
#include <functional>

namespace Control {

    namespace Private {
        template <typename Functor, typename Usage>
        class ConnectData
        {
            using Connection = Usage;
            friend typename Connection;
            using FunctorType = std::function<Functor>;
            Connection* m_pSource;
            FunctorType m_functor;

            void clear()
            {
                m_pSource = nullptr;
            }

        public:
            ConnectData(Connection* pSource, FunctorType functor)
                : m_pSource(pSource)
                , m_functor(functor)
            {}

            ConnectData()
                : m_pSource(nullptr)
            {}

            template <class... Types>
            auto operator() (Types... args) const
            {
                return m_functor(std::forward<Types>(args)...);
            }

            void Disconnect()
            {
                if (m_pSource) {
                    m_pSource->Disconnect(this);
                }
            }
        };

        template <typename Functor, typename Usage>
        class Disconnectable
        {
            using ConnectData = Private::ConnectData<Functor, Usage>;
            std::shared_ptr<ConnectData> m_spData;
        public:
            Disconnectable(std::shared_ptr<ConnectData> spData)
                : m_spData(spData)
            {}

            void Disconnect()
            {
                m_spData->Disconnect();
            }
        };

    }

    template <typename Functor>
    class Connection
    {
        using ConnectData = Private::ConnectData<Functor, Connection<Functor>>;
        friend class ConnectData;
        using FunctorType = std::function<Functor>;
        std::shared_ptr<ConnectData> m_spData;

        void Disconnect(ConnectData* pData)
        {
            if (m_spData) {
                m_spData->clear();
                m_spData.reset();
            }
        }
    public:
        Connection() = default;
        Connection(const Connection&) = delete;

        Connection(FunctorType functor)
            : m_spData(new ConnectData(this, functor))
        {}

        ~Connection()
        {
            Disconnect();
        }

        template <class... Types>
        auto operator() (Types... args) const
        {
            return (*m_spData)(std::forward<Types>(args)...);
        }

        using Disconnectable = Private::Disconnectable<Functor, Connection<Functor>>;
        Disconnectable Connect(FunctorType functor)
        {
            if (m_spData) {
                m_spData->Disconnect();
            }
            m_spData.reset(new ConnectData(this, functor));
            return Disconnectable(m_spData);
        }

        void Disconnect()
        {
            Disconnect(nullptr);
        }
    };

    template <typename Functor>
    class MultiConnection
    {
        using ConnectData = Private::ConnectData<Functor, MultiConnection<Functor>>;
        friend class ConnectData;
        using FunctorType = std::function<Functor>;
        std::set<std::shared_ptr<ConnectData>> m_setDatas;

        void Disconnect(ConnectData* pData)
        {
            auto itr = std::find_if(m_setDatas.begin(), m_setDatas.end(), [pData](const std::shared_ptr<ConnectData>& ptr) {
                return ptr.get() == pData;
            });
            if (itr != m_setDatas.end()) {
                (*itr)->clear();
                m_setDatas.erase(itr);
            }
        }
    public:
        MultiConnection() = default;
        MultiConnection(const MultiConnection&) = delete;

        ~MultiConnection()
        {
            DisconnectAll();
        }

        template <class... Types>
        void operator() (Types... args) const
        {
            for (auto& ptr : m_setDatas) {
                (*ptr)(std::forward<Types>(args)...);
            }
        }

        using Disconnectable = Private::Disconnectable<Functor, MultiConnection<Functor>>;
        Disconnectable Connect(FunctorType functor)
        {
            auto pair = m_setDatas.emplace(new ConnectData(this, functor));
            return Disconnectable(*pair.first);
        }

        void DisconnectAll()
        {
            for (auto& ptr : m_setDatas) {
                ptr->clear();
            }
            m_setDatas.clear();
        }
    };
}
