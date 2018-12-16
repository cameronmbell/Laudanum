struct Scene;
struct Event;
struct RawEvent;
struct Window;
struct Scene {
    virtual Scene* update(double delta_time)=0;
    virtual Scene* handleEvent(const Event& event)=0;
    virtual void render(Window& window) const=0;
    virtual ~Scene();
};

struct Config {
    void load() {
        // read config file
    }

    bool parseEvent(const RawEvent& rawEvent, Event& event) {
        return false;
    }
};

Config gConfig;

int main(int argc, char* argv[]) {
    gConfig.load();

    Scene* scene = nullptr;

    for (;;) {
    }
}