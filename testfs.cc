#include <uv.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char buffer[10];
uv_fs_t open_req;
uv_fs_t read_req;

void on_read(uv_fs_t *req)
{
    uv_fs_req_cleanup(req);
    if (req->result == 0) {
        uv_fs_t close_req;
        uv_fs_close(uv_default_loop(), &close_req, req->result, NULL);
    }
    else
    {
        printf("%s", buffer);
        memset(buffer, 0, sizeof(buffer));
        uv_fs_read(uv_default_loop(), &read_req, open_req.result, buffer, sizeof(buffer), -1, on_read);
    }
}

void on_open(uv_fs_t *req)
{
  memset(buffer, 0, sizeof(buffer));
    uv_fs_read(uv_default_loop(), &read_req, req->result, buffer, sizeof(buffer), -1, on_read);
    uv_fs_req_cleanup(req);
}

int main(int argc, char **argv)
{
    uv_fs_open(uv_default_loop(), &open_req, argv[1], O_RDONLY, 0, on_open);
    uv_run(uv_default_loop(), UV_RUN_DEFAULT);
    return 0;
}
