// flavor text
struct flavor_text {
    char personnell[16];
    int weight;
    char alignment[16];
};

// for flight level view
struct level_data {
    int x;
    int y;
    char data[16];
    bool persistent;
    char type;
    unsigned char num;
    const flavor_text * flavor_data;
};

// for info on each tile in sector
struct tile_data {
    int x;
    int y;
    char data[16];
    int num_level_data;
    const level_data * flight_data;
};

