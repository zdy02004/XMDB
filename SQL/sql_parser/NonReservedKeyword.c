#include <stdio.h>
#include <ctype.h>
#include <strings.h>
#include "parser.hh"

static const NonReservedKeyword None_reserved_keywords[] = {
  {"auto_increment", AUTO_INCREMENT},
  {"chunkserver", CHUNKSERVER},
  {"compress_method", COMPRESS_METHOD},
  {"consistent_mode", CONSISTENT_MODE},
  {"expire_info", EXPIRE_INFO},
  {"grants", GRANTS},
  {"join_info", JOIN_INFO},
  {"mergeserver", MERGESERVER},
  {"replica_num", REPLICA_NUM},
  {"rootserver", ROOTSERVER},
  {"row_count", ROW_COUNT},
  {"server", SERVER},
  {"server_ip", SERVER_IP},
  {"server_port", SERVER_PORT},
  {"server_type", SERVER_TYPE},
  {"status", STATUS},
  {"table_id", TABLE_ID},
  {"tablet_block_size", TABLET_BLOCK_SIZE},
  {"tablet_max_size", TABLET_MAX_SIZE},
  {"unlocked", UNLOCKED},
  {"updateserver", UPDATESERVER},
  {"use_bloom_filter", USE_BLOOM_FILTER},
  {"variables", VARIABLES},
  {"verbose", VERBOSE},
  {"warnings", WARNINGS},
};

const NonReservedKeyword *non_reserved_keyword_lookup(const char *word)
{
  int size = sizeof (None_reserved_keywords) / sizeof ((None_reserved_keywords)[0]);
  const NonReservedKeyword *low = &None_reserved_keywords[0];
  const NonReservedKeyword *high = &None_reserved_keywords[size - 1];
  const NonReservedKeyword *middle = NULL;

  while (low <= high)
  {
    middle = low + (high - low) / 2;
    int ret = 0;
    /* make sure word is '\0' ended */
    if ((ret = strcasecmp(middle->keyword_name, word)) == 0)
      break;
    else if (ret < 0)
      low = middle + 1;
    else
      high = middle -1;
  }
  if (low > high)
    middle = NULL;
  return middle;
}

