#pragma once
/*
 * Copyright (c) 2016-20017 Max Cong <savagecm@qq.com>
 * this code can be found at
 * https://github.com/maxcong001/design_pattern/edit/master/include/singleton/singleton.hpp
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <mutex>
template <typename T>
class Singleton
{
public:
  template <typename... Args>
  static T *Instance(Args &&... args);

  static T *Instance();
  static T *GetInstance();

  static void DestroyInstance();

private:
  Singleton(void);
  virtual ~Singleton(void);
  Singleton(const Singleton &);
  Singleton &operator=(const Singleton &);

private:
  static T *m_pInstance;
  static std::mutex mtx;
};

template <typename T>
T *Singleton<T>::m_pInstance = nullptr;
template <typename T>
std::mutex Singleton<T>::mtx;

template <typename T>
template <class... Args>
T *Singleton<T>::Instance(Args &&... args)
{
  std::lock_guard<std::mutex> lck(mtx);
  if (m_pInstance == nullptr)
    m_pInstance = new T(std::forward<Args>(args)...);
  return m_pInstance;
}

template <typename T>
T *Singleton<T>::Instance()
{
  std::lock_guard<std::mutex> lck(mtx);
  if (m_pInstance == nullptr)
    m_pInstance = new T();
  return m_pInstance;
}

template <typename T>
T *Singleton<T>::GetInstance()
{
  std::lock_guard<std::mutex> lck(mtx);
  if (m_pInstance == nullptr)
    throw std::logic_error(
        "the instance is not init, please initialize the instance first");
  return m_pInstance;
}

template <typename T>
void Singleton<T>::DestroyInstance()
{
  std::lock_guard<std::mutex> lck(mtx);
  delete m_pInstance;
  m_pInstance = nullptr;
}
