/*
 * Copyright (C) 2015 Niek Linnenbank
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <FreeNOS/System.h>
#include <Index.h>
#include <MemoryChannel.h>
#include "mpi.h"
#include "MPIMessage.h"

extern Index<MemoryChannel> *readChannel;

int MPI_Recv(void *buf,
             int count,
             MPI_Datatype datatype,
             int source,
             int tag,
             MPI_Comm comm,
             MPI_Status *status)
{
    MPIMessage msg;
    MemoryChannel *ch;

    if (datatype != MPI_INT)
        return MPI_ERR_UNSUPPORTED_DATAREP;

    if (!(ch = (MemoryChannel *) readChannel->get(source)))
        return MPI_ERR_RANK;

    for (int i = 0; i < count; i++)
    {
        while (ch->read(&msg) != Channel::Success)
            ;
        *(((int *) buf) + i) = msg.integer;
    }
    return MPI_SUCCESS;
}
