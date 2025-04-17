/* See LICENSE file for copyright and license details. */

#include "prci.h"

volatile Prci *const prci __attribute__((used)) = (volatile Prci *)PRCI_BASE;
