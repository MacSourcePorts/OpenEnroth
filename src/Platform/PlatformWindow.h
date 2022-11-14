#pragma once

#include <string>
#include <memory>

#include "Utility/Geometry/Size.h"
#include "Utility/Geometry/Point.h"

#include "PlatformOpenGLOptions.h"

class PlatformOpenGLContext;

class PlatformWindow {
 public:
    virtual ~PlatformWindow() = default;

    virtual void SetTitle(const std::string &title) = 0;
    virtual std::string Title() const = 0;

    virtual void Resize(const Sizei &size) = 0;
    virtual Sizei Size() const = 0;

    virtual void SetPosition(const Pointi &pos) = 0;
    virtual Pointi Position() const = 0;

    virtual void SetVisible(bool visible) = 0;
    virtual bool IsVisible() const = 0;

    virtual void SetFullscreen(bool fullscreen) = 0;
    virtual bool IsFullscreen() const = 0;

    virtual void SetFrameless(bool frameless) = 0;
    virtual bool IsFrameless() const = 0;

    virtual void SetGrabsMouse(bool grabsMouse) = 0;
    virtual bool GrabsMouse() const = 0;

    virtual void Activate() = 0;

    virtual uintptr_t SystemHandle() const = 0;

    virtual std::unique_ptr<PlatformOpenGLContext> CreateOpenGLContext(const PlatformOpenGLOptions &options) = 0;

    // TODO(captainurist): compat methods, drop
    int GetWidth() const {
        return Size().w;
    }

    int GetHeight() const {
        return Size().h;
    }
};
