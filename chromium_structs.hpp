#pragma once

#include <cstdint>
#include <utility>
#include <vector>

void CloseFD(int fd);

class ScopedFD {
 public:
  ScopedFD() {}
  explicit ScopedFD(int fd) : fd_(fd) {}
  ScopedFD(ScopedFD &&other) { *this = std::move(other); }
  ScopedFD(const ScopedFD &) = delete;

  ~ScopedFD() { reset(); }

  ScopedFD &operator=(const ScopedFD &) = delete;
  ScopedFD &operator=(ScopedFD &&other) {
    reset();
    fd_ = other.fd_;
    other.fd_ = -1;
    return *this;
  }

  explicit operator bool() const { return fd_ >= 0; }

  int get() const { return fd_; }

  void reset() {
    if (fd_ >= 0) {
      //CloseFD(fd_);
    }
    fd_ = -1;
  }

  int release() {
    int fd = fd_;
    fd_ = -1;
    return fd;
  }

 private:
  int fd_ = -1;
};

struct NativePixmapPlane {
  uint32_t stride;
  uint64_t offset;
  uint64_t size;
  int fd;
};

struct NativePixmapHandle {
  static constexpr uint64_t kNoModifier = 0x00ffffffffffffffULL;
  std::vector<NativePixmapPlane> planes;
  uint64_t modifier = kNoModifier;
  //bool flaga;
};


