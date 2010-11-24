#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <curl/types.h>
#include <curl/easy.h>

typedef struct _bucket
{
  u_int idx;
  u_int size;
  unsigned char *data;
} bucket_t;


char G_KEY[32];
char G_SECRET[64];

int cloud_this(bucket_t bucket, CURL* curl)
{
  struct curl_slist *slist = NULL;

  //  slist = curl_slist_append(slist, "");
  //  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist);

  curl_easy_setopt(curl, CURLOPT_PUT, 1L);

  curl_easy_setopt(curl, CURLOPT_WRITEDATA, bucket.data);  

  curl_easy_perform(curl);

  curl_slist_free_all(slist);
  

  return 0;
}

int main(int argc, char *argv[])
{
  const int MAX = 64;
  bucket_t b;
  char header[MAX];

  assert(argc == 2);

  FILE *file = fopen(argv[1], "r");
  assert(file);

  FILE *key = fopen("./secret", "r");
  assert(key);
  fread(G_KEY, 1, 32, key);
  fread(G_SECRET, 1, 32, key);

  CURL *curl = curl_easy_init();
  assert(curl);

  while(fgets(header, MAX, file))
    {
      int ret = sscanf(header, "%u %u", &b.idx, &b.size);
      assert(ret == 2);
      b.data = malloc(b.size);
      fread(b.data, 1, b.size, file);
      //      printf("ENTRY: %d, %d [%s]\n", handle_id, num_bytes, buffer);
      cloud_this(b, curl);
      free(b.data);
    }


  curl_easy_cleanup(curl);

  exit(0);
}