#include "sids.h"
#include "definitions.h"

struct sid *sid0 = (struct sid *)SID0_BASE_ADDRESS;
struct sid *sid1 = (struct sid *)SID1_BASE_ADDRESS;

void sids_reset()
{
    sid0->filter_mode_volume = 15;
}
