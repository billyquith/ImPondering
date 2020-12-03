
namespace eg {

    struct Init {
        unsigned screenW, screenH;
    };

    void init(const Init&);

    struct Update {
        float dt;
        unsigned frameNum;
    };

    bool update(const Update&);

} // namespace eg

