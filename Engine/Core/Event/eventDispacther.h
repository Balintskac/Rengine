#pragma once 

#include <string>
#include <vector>
#include <type_traits>
#include <functional>
#include <typeindex>
#include "iostream"

struct KeyboardEvent {
	int keyCode;
	bool isPressed;
};

struct MouseEvent {
	double x, y;
	int button;
	int mods;
};

class EventDispacther
{

public:

	// Add listener for EventType
	template<typename EventType>
	void addListener(std::function<void(EventType&)> cb) {
		auto& listeners = getListeners<EventType>();
		listeners.emplace_back(std::move(cb));
	}

	// Trigger event, calls all listeners for that event type
	template<typename EventType>
	void trigger(EventType& event) {
		auto& listeners = getListeners<EventType>();
		for (auto& listener : listeners) {
			listener(event);
		}
	}
private:

	// Base class for type-erased listener storage
	struct BaseListeners {
		virtual ~BaseListeners() = default;
	};

	// Typed listener storage for EventType
	template<typename EventType>
	struct Listeners : BaseListeners {
		std::vector<std::function<void(EventType&)>> listeners;
	};

	// Get listeners vector for EventType, create if missing
	template<typename EventType>
	std::vector<std::function<void(EventType&)>>& getListeners() {
		std::type_index typeId = std::type_index(typeid(EventType));

		if (listenersMap.find(typeId) == listenersMap.end()) {
			listenersMap[typeId] = std::make_unique<Listeners<EventType>>();
		}

		auto basePtr = listenersMap[typeId].get();
		auto typedPtr = static_cast<Listeners<EventType>*>(basePtr);
		return typedPtr->listeners;
	}

	std::unordered_map<std::type_index, std::unique_ptr<BaseListeners>> listenersMap;
};