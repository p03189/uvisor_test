/*
 * Copyright (c) 2013-2016, ARM Limited, All Rights Reserved
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "mbed.h"
#include "uvisor-lib/uvisor-lib.h"

typedef struct {
	uint32_t data;
	int caller_id;
} my_box_context;

static const UvisorBoxAclItem acl[] = {
        {(void *)0x40000000, 0x100000, UVISOR_TACLDEF_PERIPH}, /* Peripheral */
};

static void my_box_main(const void *);
uint32_t get_mybox_context(void);

/* Box configuration
 * We need 1kB of stack both in the main and interrupt threads as both of them
 * use printf. */
UVISOR_BOX_NAMESPACE(NULL);
UVISOR_BOX_HEAPSIZE(3072);
UVISOR_BOX_MAIN(my_box_main, osPriorityNormal, 1024);
UVISOR_BOX_CONFIG(my_box, acl, 1024, my_box_context);

static void my_box_main(const void *)
{
    /* Allocate the serial port to ensure that code in this secure box won't
     * touch handles in the default security context when printing. */
    RawSerial * pc;
    if (!(pc = new RawSerial(USBTX, USBRX))) {
        return;
    }

    while(1) {
    	pc->printf("\r\n***** Secure BOX *****\r\n");
    }

}
