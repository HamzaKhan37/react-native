/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <fbjni/fbjni.h>
#include <glog/logging.h>
#include <jsi/jsi.h>
#include <react/utils/ContextContainer.h>
#include <mutex>
#include <unordered_set>

#include <react/cxxcomponents/ComponentManager.h>
#include <react/fabric/ComponentRegistryResolver.h>

namespace facebook {
namespace react {

class Instance;

class CppComponentRegistry : public jni::HybridClass<CppComponentRegistry> {
 public:
  constexpr static const char *const kJavaDescriptor =
      "Lcom/facebook/react/fabric/CppComponentRegistry;";

  static void registerNatives();

  void addComponentManager(
      std::string name,
      bool isRootComponent,
      std::function<std::shared_ptr<facebook::react::ComponentManager>(
          const std::string &name)> f);

  bool containsComponentManager(std::string name) const;

  std::shared_ptr<facebook::react::ComponentManager> getComponentManager(
      const std::string &name) const;

 private:
  static jni::local_ref<jhybriddata> initHybrid(jni::alias_ref<jclass>);
  ComponentRegistryResolver componentManagerResolver_{};
};

} // namespace react
} // namespace facebook
