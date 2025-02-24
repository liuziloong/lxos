/*
 * Copyright 2023 Andy andrew.lxos@gmail.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "lx/types.h"
#include "lx/stdlib.h"

char *itoa(int val, char *str, int radix)
{
    const char digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";

    char c = '\0';
	int  i = 0;
    int  j = 0;

    if ((str == NULL) || (radix < 2) || (radix > 36)) {
        return NULL;
    }

    if ((radix == 10) && (val < 0)) {
        str[i++] = '-';
        val = -val;
	}

    do {
        str[i++] = digits[val % radix];
    } while ((val /= radix) != 0);

    str[i] = '\0';

    for (j = 0, i--; j < i; j++, i--) {
        c = str[j];
        str[j] = str[i];
        str[i] = c;
    }

    return str;
}

/*
int atoi(const char *str)
{
    return 0;
}
*/

