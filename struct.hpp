// for flight level view
typedef struct level_data {
    int x;
    int y;
    char data[16];
    bool persistent;
    char type;
    unsigned char num;
};

// for info on each tile in sector
typedef struct tile_data {
    int x;
    int y;
    char data[16];
    int num_level_data;
    const level_data * flight_data;
};
