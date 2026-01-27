/*
 * Copyright (C) Henrique Barateli, <henriquejb194@gmail.com>, et al.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#pragma once

#include <iterator>
#include <list>
#include <unordered_map>

template<typename Key, typename Value>
class LruCache {
  public:
    using KeyValuePair = std::pair<Key, Value>;
    using ListIterator = std::list<KeyValuePair>::iterator;

    explicit LruCache(size_t max_size)
        : max_size(max_size) {
    }

    void put(const Key& key, Value value) {
        if (auto it{items_map.find(key)}; it != items_map.end()) {
            it->second->second = std::move(value);
            items_list.splice(items_list.begin(), items_list, it->second);
            return;
        }

        items_list.emplace_front(key, std::move(value));
        items_map.emplace(key, items_list.begin());

        if (items_map.size() > max_size) {
            auto last{std::prev(items_list.end())};
            items_map.erase(last->first);
            items_list.pop_back();
        }
    }

    const Value* get(const Key& key) {
        auto it{items_map.find(key)};
        if (it == items_map.end()) {
            return nullptr;
        }
        items_list.splice(items_list.begin(), items_list, it->second);
        return &it->second->second;
    }

    bool exists(const Key& key) const {
        return items_map.contains(key);
    }

    [[nodiscard]]
    size_t size() const {
        return items_map.size();
    }

  private:
    std::list<KeyValuePair> items_list;
    std::unordered_map<Key, ListIterator> items_map;
    size_t max_size;
};
