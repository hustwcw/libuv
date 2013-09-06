#include <stdio.h>
#include "include/uv.h"

int count = 0;

void wait_for_a_while1(uv_idle_t *handle, int status)
{
    count++;

    printf("count1: %d\n", count);
    if (count > 10) {
        uv_idle_stop(handle);
    }
}
void wait_for_a_while2(uv_idle_t *handle, int status)
{
    count++;

    printf("count2: %d\n", count);
    if (count > 10) {
        uv_idle_stop(handle);
    }
}
int main()
{
    uv_idle_t idler1;
    uv_idle_t idler2;

    printf("version:%s\n", uv_version_string());
    uv_idle_init(uv_default_loop(), &idler1);
    uv_idle_init(uv_default_loop(), &idler2);
    uv_idle_start(&idler1, wait_for_a_while1);
    uv_idle_start(&idler2, wait_for_a_while2);

    printf("Idling...\n");
    uv_run(uv_default_loop(), UV_RUN_DEFAULT);
    return 0;
}
