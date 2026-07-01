#pragma once

#include <functional>
#include <list>
#include <algorithm>

// TODO: Make Thead-Safe
//! An Event Handler is the Subscriber to an Event that calls a Function when notified by the Event
template<typename... Args>
class EventHandler {
public:
    //! A Function Type is a typedef for a function with a void return value and flexible Arguments
    typedef std::function<void(Args...)> functionType;
    typedef unsigned int handlerId;

    EventHandler() : m_Id(idCounter++) {
    }

    //! Increments the intern ID Counter and assigns the Function to the Handler
    explicit EventHandler(const functionType &function) : m_Function(function) {
        m_Id = ++idCounter;
    }

    // -- Operator
    //! Invokes the Function
    void operator()(Args... params) const {
        if (m_Function)
            m_Function(params...);
    }

    //! Compares the Handlers ID with the other ID
    bool operator==(const EventHandler &other) const {
        return m_Id == other.m_Id;
    }

    void SetFunction(const functionType &function) { m_Function = function; }

    // -- Getter
    handlerId GetID() const {
        return m_Id;
    }

private:
    //! ID of the Handler
    handlerId m_Id;

    //! Function that gets called when notified
    functionType m_Function;

    //! Intern Counter that keeps track of the amount of Handlers
    static unsigned int idCounter;
};

template<typename... Args>
unsigned int EventHandler<Args...>::idCounter;

template<typename... Args>
class Event {
public:
    typedef EventHandler<Args...> eventHandlerType;

    //! The Subscriber will get notified and invoke its function when the Event is dispatched
    void Subscribe(const eventHandlerType &subscriber) {
        m_Handlers.push_back(subscriber);
    }

    //! The Subscriber will no longer get notified when the Event is dispatched
    void Unsubscribe(const eventHandlerType &subscriber) {
        auto it = std::find(m_Handlers.begin(), m_Handlers.end(), subscriber);
        if (it != m_Handlers.end())
            m_Handlers.erase(it);
    }

    //! Notifies every Event Handler that this Event was triggered with the given Arguments
    void Dispatch(Args... params) {
        for (const auto &subscriber: m_Handlers) {
            subscriber(params...);
        }
    }

    // -- Operator(For Usage Convenience)
    void operator+=(const eventHandlerType &other) {
        Subscribe(other);
    }

    void operator-=(const eventHandlerType &other) {
        Unsubscribe(other);
    }

private:
    //! A List of all Handlers
    std::list<eventHandlerType> m_Handlers;
};
