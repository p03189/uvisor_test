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
#include "uvisor-lib/uvisor-lib.h"
#include "mbed.h"
#include "main-hw.h"

/* Create ACLs for main box. */
MAIN_ACL(g_main_acl);

/* Enable uVisor. */
UVISOR_SET_MODE_ACL(UVISOR_ENABLED, g_main_acl);
UVISOR_SET_PAGE_HEAP(8 * 1024, 5);

int sub_thread(void) {
    while(1)
        printf("\r\n***** sub_thread *****\r\n");
}

int main(void) {

    //size_t count = 0;

    osThreadId_t result = osThreadNew((osThreadFunc_t)sub_thread, NULL, NULL);
    if (result == NULL)
	printf("\r\n sub_thread creating is failed \r\n");

    while (1)
        printf("\r\n***** PUBLIC BOX *****\r\n");

    return 0;
}
