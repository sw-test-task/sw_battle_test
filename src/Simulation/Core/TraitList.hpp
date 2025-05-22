#pragma once

#include <any>
#include <stdexcept>
#include <typeindex>
#include <unordered_map>

namespace sw
{
	template <class T>
	concept IsTrivialTrait = T::IsTrivial;

	/**
	 * Container for different traits (characteristics/abilities/etc). Usage:
	 *
	 * struct HP : public TrivialTrait<uint32_t>
	 * {};
	 *
	 * list.add<HP>(42);
	 * bool contains = list.has<HP>();
	 * uint32_t& hp = list.get<HP>();
	 * list.set<HP>(hp);
	 */
	class TraitList
	{
		using MapType = std::unordered_map<std::type_index, std::any>;
		using Iterator = MapType::iterator;
		using ConstIterator = MapType::const_iterator;

	public:
		template <IsTrivialTrait T>
		void set(const T::type& value)
		{
			_traits[typeid(T)] = T{{.value = value}};
		}

		template <class T>
		void set(const T& trait)
		{
			_traits[typeid(T)] = trait;
		}

		template <class T>
		T& get()
		{
			return expectValue<T>(find<T>());
		}

		template <class T>
		const T& get() const
		{
			return expectValue<T>(find<T>());
		}

		template <IsTrivialTrait T>
		T::type& get()
		{
			return expectValue<T>(find<T>()).value;
		}

		template <IsTrivialTrait T>
		const T::type& get() const
		{
			return expectValue<T>(find<T>()).value;
		}

		template <IsTrivialTrait T>
		const T::type& getOrDefault(T::type def = typename T::type{}) const
		{
			return valueOrDefault<T>(find<T>(), def);
		}

		template <class T>
		bool has() const
		{
			return _traits.contains(typeid(T));
		}

	private:
		template <class T>
		Iterator find()
		{
			return _traits.find(typeid(T));
		}

		template <class T>
		ConstIterator find() const
		{
			return _traits.find(typeid(T));
		}

		template <class T>
		T& expectValue(Iterator it)
		{
			if (it == _traits.end())
			{
				throw std::runtime_error("trait was not found");
			}

			return std::any_cast<T&>(it->second);
		}

		template <class T>
		const T& expectValue(ConstIterator it) const
		{
			if (it == _traits.end())
			{
				throw std::runtime_error("trait was not found");
			}

			return std::any_cast<const T&>(it->second);
		}

		template <class T, class D>
		const D& valueOrDefault(ConstIterator it, const D& def) const
		{
			if (it == _traits.end())
			{
				return def;
			}

			return std::any_cast<const T&>(it->second).value;
		}

		MapType _traits;
	};
}
