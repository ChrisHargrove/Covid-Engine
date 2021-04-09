#pragma once

#include <string>
#include <vector>
#include <functional>

namespace Covid
{
    template <class ...Args>
    struct ActionCallback
    {
    public:
        ActionCallback(std::string id, std::function<void(Args... args)> callback)
        {
            m_id = id;
            m_callback = callback;
        }

        std::string m_id;
        std::function<void(Args... args)> m_callback;
    };

    template <class ... Args>
    class Action
    {
    public:
        void Subscribe(std::string id, std::function<void(Args... args)> callback)
        {
            m_callbacks.emplace_back(id, callback);
        }

        void Unsubscribe(std::string id)
        {
            m_callbacks.erase(std::remove_if(m_callbacks.begin(), m_callbacks.end(), [](ActionCallback<Args...> callback) { return callback.m_id == id; }), m_callbacks.end());
        }

        void Invoke(Args ... args)
        {
            for each (ActionCallback<Args...> actionCallback in m_callbacks)
            {
                actionCallback.m_callback(args...);
            }
        }

    private:
        std::vector<ActionCallback<Args...>> m_callbacks;

    };
}
