#ifndef GEN_TILE_H
#define GEN_TILE_H

#include "protocol.h"
#include <limits.h> /* for PATH_MAX */

#ifdef __cplusplus
extern "C" {
#endif

enum queueEnum {queueRequest, queueRequestPrio, queueRequestBulk, queueDirty, queueRender,  queueDuplicate, queueRequestLow};

struct item {
    struct item *next;
    struct item *prev;
    struct protocol req;
    int mx, my;
    int fd;
    struct item *duplicates;
    enum queueEnum inQueue;
    enum queueEnum originatedQueue;
};

//int render(Map &m, int x, int y, int z, const char *filename);
void *render_thread(void *);
struct item *fetch_request(void);
void delete_request(struct item *item);
void render_init(const char *plugins_dir, const char* font_dir, int font_recurse);
void get_shp_set_params(char * shpconf_file, int maxzoom, double * minData, double * maxData);

typedef struct {
    char name[XMLCONFIG_MAX];
    char file[PATH_MAX];
    double upper;
    double lower;
    int minzoom;
    int maxzoom;
} shpconfig;

typedef struct {
    void * obj;
    char * name;
    char * file;
    int minzoom;
    int maxzoom;
} shpset;

void shpset_init(shpset * shp_set, shpconfig * shp_conf);
void shpset_delete(shpset * shp_set);
void create_shpset(double minData, double maxData, char * colorScale, shpconfig * shp_conf, shpset * shp_set);

#ifdef __cplusplus
}
#endif

#endif
