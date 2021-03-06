/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "EventIdMap.hpp"

using namespace apache::geode::client;

EventIdMap::~EventIdMap() { clear(); }

void EventIdMap::init(std::chrono::milliseconds expirySecs) {
  m_expiry = expirySecs;
}

void EventIdMap::clear() {
  GUARD_MAP;
  m_map.clear();
}

EventIdMapEntry EventIdMap::make(std::shared_ptr<EventId> eventid) {
  auto sid = std::make_shared<EventSource>(
      eventid->getMemId(), eventid->getMemIdLen(), eventid->getThrId());
  auto seq = std::make_shared<EventSequence>(eventid->getSeqNum());
  return std::make_pair(sid, seq);
}

bool EventIdMap::isDuplicate(std::shared_ptr<EventSource> key,
                             std::shared_ptr<EventSequence> value) {
  GUARD_MAP;
  const auto& entry = m_map.find(key);

  if (entry != m_map.end() && ((*value) <= (*(entry->second)))) {
    return true;
  }
  return false;
}

bool EventIdMap::put(std::shared_ptr<EventSource> key,
                     std::shared_ptr<EventSequence> value, bool onlynew) {
  GUARD_MAP;

  value->touch(m_expiry);

  const auto& entry = m_map.find(key);

  if (entry != m_map.end()) {
    if (onlynew && ((*value) <= (*(entry->second)))) {
      return false;
    } else {
      m_map[key] = value;
      return true;
    }
  } else {
    m_map[key] = value;
    return true;
  }
}

bool EventIdMap::touch(std::shared_ptr<EventSource> key) {
  GUARD_MAP;

  const auto& entry = m_map.find(key);

  if (entry != m_map.end()) {
    entry->second->touch(m_expiry);
    return true;
  } else {
    return false;
  }
}

bool EventIdMap::remove(std::shared_ptr<EventSource> key) {
  GUARD_MAP;

  const auto& entry = m_map.find(key);

  if (entry != m_map.end()) {
    m_map.erase(key);
    return true;
  } else {
    return false;
  }
}

// side-effect: sets acked flags to true
EventIdMapEntryList EventIdMap::getUnAcked() {
  GUARD_MAP;

  EventIdMapEntryList entries;

  for (const auto& entry : m_map) {
    if (entry.second->getAcked()) {
      continue;
    }

    entry.second->setAcked(true);
    entries.push_back(std::make_pair(entry.first, entry.second));
  }

  return entries;
}

uint32_t EventIdMap::clearAckedFlags(EventIdMapEntryList& entries) {
  GUARD_MAP;

  uint32_t cleared = 0;

  for (const auto& item : entries) {
    const auto& entry = m_map.find((item).first);

    if (entry != m_map.end()) {
      entry->second->setAcked(false);
      cleared++;
    }
  }

  return cleared;
}

uint32_t EventIdMap::expire(bool onlyacked) {
  GUARD_MAP;

  uint32_t expired = 0;

  EventIdMapEntryList entries;

  ACE_Time_Value current = ACE_OS::gettimeofday();

  for (const auto& entry : m_map) {
    if (onlyacked && !entry.second->getAcked()) {
      continue;
    }

    if (entry.second->getDeadline() < current) {
      entries.push_back(std::make_pair(entry.first, entry.second));
    }
  }

  for (EventIdMapEntryList::iterator expiry = entries.begin();
       expiry != entries.end(); expiry++) {
    m_map.erase((*expiry).first);
    expired++;
  }

  return expired;
}

void EventSequence::init() {
  m_seqNum = -1;
  m_acked = false;
  m_deadline = ACE_OS::gettimeofday();
}

void EventSequence::clear() { init(); }

EventSequence::EventSequence() { init(); }

EventSequence::EventSequence(int64_t seqNum) {
  init();
  m_seqNum = seqNum;
}

EventSequence::~EventSequence() { clear(); }

void EventSequence::touch(std::chrono::milliseconds ageSecs) {
  m_deadline = ACE_OS::gettimeofday();
  m_deadline += ageSecs;
}

void EventSequence::touch(int64_t seqNum, std::chrono::milliseconds ageSecs) {
  touch(ageSecs);
  m_seqNum = seqNum;
  m_acked = false;
}

int64_t EventSequence::getSeqNum() { return m_seqNum; }

void EventSequence::setSeqNum(int64_t seqNum) { m_seqNum = seqNum; }

bool EventSequence::getAcked() { return m_acked; }

void EventSequence::setAcked(bool acked) { m_acked = acked; }

ACE_Time_Value EventSequence::getDeadline() { return m_deadline; }

void EventSequence::setDeadline(ACE_Time_Value deadline) {
  m_deadline = deadline;
}

bool EventSequence::operator<=(const EventSequence& rhs) const {
  return this->m_seqNum <= (&rhs)->m_seqNum;
}
