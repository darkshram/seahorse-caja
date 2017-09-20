/*
 *  Seahorse
 *
 *  Copyright (C) 2005 Tecsidel S.A.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public
 *  License along with this library; if not, write to the Free
 *  Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *  Author: Fernando Herrera <fernando.herrera@tecsidel.es>
 *          Stef Walter <stef@memberwebs.com>
 *
 */

#ifndef SEAHORSE_CAJA_H
#define SEAHORSE_CAJA_H

#include <glib-object.h>

G_BEGIN_DECLS

#define SEAHORSE_TYPE_CAJA  (seahorse_caja_get_type ())
#define SEAHORSE_CAJA(o)    (G_TYPE_CHECK_INSTANCE_CAST ((o), SEAHORSE_TYPE_CAJA, CajaFr))
#define SEAHORSE_IS_CAJA(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), SEAHORSE_TYPE_CAJA))

typedef struct _SeahorseCaja      SeahorseCaja;
typedef struct _SeahorseCajaClass SeahorseCajaClass;

struct _SeahorseCaja {
	GObject __parent;
};

struct _SeahorseCajaClass {
	GObjectClass __parent;
};

GType seahorse_caja_get_type      (void);
void  seahorse_caja_register_type (GTypeModule *module);

G_END_DECLS

#endif /* CAJA_FILEROLLER_H */
