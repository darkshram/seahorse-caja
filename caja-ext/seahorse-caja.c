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
 *  Authors: Fernando Herrera <fernando.herrera@tecsidel.es>
 *           Stef Walter <stef@memberwebs.com>
 */

#include <config.h>
#include <string.h>
#include <glib/gi18n-lib.h>
#include <libcaja-extension/caja-extension-types.h>
#include <libcaja-extension/caja-file-info.h>
#include <libcaja-extension/caja-menu-provider.h>
#include "seahorse-caja.h"

static GObjectClass *parent_class;

static void
crypt_callback (CajaMenuItem *item, gpointer user_data)
{
    GList *files, *scan;
    char *uri, *t;
    GString *cmd;

    files = g_object_get_data (G_OBJECT (item), "files");
    g_assert (files != NULL);

    cmd = g_string_new ("mate-seahorse-tool");
    g_string_append_printf (cmd, " --encrypt");

    for (scan = files; scan; scan = scan->next) {
        uri = caja_file_info_get_uri ((CajaFileInfo*)scan->data);
        t = g_shell_quote (uri);
        g_free (uri);

        g_string_append_printf (cmd, " %s", t);
        g_free (t);
    }

    g_print ("EXEC: %s\n", cmd->str);
    g_spawn_command_line_async (cmd->str, NULL);

    g_string_free (cmd, TRUE);
}

static void
sign_callback (CajaMenuItem *item, gpointer user_data)
{
    GList *files, *scan;
    char *uri, *t;
    GString *cmd;

    cmd = g_string_new ("mate-seahorse-tool");
    g_string_append_printf (cmd, " --sign");
    files = g_object_get_data (G_OBJECT (item), "files");
    g_assert (files != NULL);

    for (scan = files; scan; scan = scan->next) {
        uri = caja_file_info_get_uri ((CajaFileInfo*)scan->data);
        t = g_shell_quote (uri);
        g_free (uri);

        g_string_append_printf (cmd, " %s", t);
        g_free (t);
    }

    g_print ("EXEC: %s\n", cmd->str);
    g_spawn_command_line_async (cmd->str, NULL);

    g_string_free (cmd, TRUE);
}

static char *pgp_encrypted_types[] = {
    "application/pgp",
    "application/pgp-encrypted",
    NULL
};

static char *no_display_types[] = {
    "application/x-desktop",
    NULL
};

static gboolean
is_mime_types (CajaFileInfo *file, char* types[])
{
    int i;

    for (i = 0; types[i] != NULL; i++)
        if (caja_file_info_is_mime_type (file, types[i]))
            return TRUE;

    return FALSE;
}

static gboolean
is_all_mime_types (GList *files, char* types[])
{
    while (files) {
        if (!is_mime_types ((CajaFileInfo*)(files->data), types))
            return FALSE;
        files = g_list_next (files);
    }

    return TRUE;
}

static GList*
seahorse_caja_get_file_items (CajaMenuProvider *provider,
                                  GtkWidget *window, GList *files)
{
    CajaMenuItem *item;
    GList *scan, *items = NULL;
    gboolean xnaut;
    guint num;
    gchar *uri;

    num = g_list_length (files);

    /* No files */
    if (num == 0)
        return NULL;

    /* Check if it's a desktop file. Copied from caja-send extension */
    for (scan = files; scan; scan = scan->next) {
        uri = caja_file_info_get_uri ((CajaFileInfo*)(scan->data));
        xnaut = (uri != NULL && g_ascii_strncasecmp (uri, "x-caja-desktop", 18) == 0);
        g_free (uri);
        if (xnaut)
            return NULL;
    }

    /* A single encrypted file, no menu items */
    if (num == 1 &&
        is_mime_types ((CajaFileInfo*)files->data, pgp_encrypted_types))
        return NULL;

    /* All 'no display' types, no menu items */
    if (is_all_mime_types (files, no_display_types))
        return NULL;

    item = caja_menu_item_new ("CajaSh::crypt", _("Encrypt..."),
        ngettext ("Encrypt (and optionally sign) the selected file", "Encrypt the selected files", num), NULL);
    g_object_set_data_full (G_OBJECT (item), "files", caja_file_info_list_copy (files),
                                 (GDestroyNotify) caja_file_info_list_free);
    g_signal_connect (item, "activate", G_CALLBACK (crypt_callback), provider);
    items = g_list_append (items, item);

    item = caja_menu_item_new ("CajaSh::sign", _("Sign"),
        ngettext ("Sign the selected file", "Sign the selected files", num), NULL);
    g_object_set_data_full (G_OBJECT (item), "files", caja_file_info_list_copy (files),
                                (GDestroyNotify) caja_file_info_list_free);
    g_signal_connect (item, "activate", G_CALLBACK (sign_callback), provider);

    items = g_list_append (items, item);
    return items;
}

static void
seahorse_caja_menu_provider_iface_init (CajaMenuProviderIface *iface)
{
    iface->get_file_items = seahorse_caja_get_file_items;
}

static void
seahorse_caja_instance_init (SeahorseCaja *sh)
{

}

static void
seahorse_caja_class_init (SeahorseCajaClass *klass)
{
    parent_class = g_type_class_peek_parent (klass);
}

static GType seahorse_caja_type = 0;

GType
seahorse_caja_get_type (void)
{
    return seahorse_caja_type;
}

void
seahorse_caja_register_type (GTypeModule *module)
{
    static const GTypeInfo info = {
        sizeof (SeahorseCajaClass), (GBaseInitFunc)NULL,
        (GBaseFinalizeFunc)NULL, (GClassInitFunc)seahorse_caja_class_init,
        NULL, NULL, sizeof(SeahorseCaja), 0,
        (GInstanceInitFunc)seahorse_caja_instance_init,
    };

    static const GInterfaceInfo menu_provider_iface_info = {
        (GInterfaceInitFunc)seahorse_caja_menu_provider_iface_init,
        NULL, NULL
    };

    seahorse_caja_type = g_type_module_register_type (module,
                    G_TYPE_OBJECT, "SeahorseCaja", &info, 0);

    g_type_module_add_interface (module, seahorse_caja_type,
                    CAJA_TYPE_MENU_PROVIDER, &menu_provider_iface_info);
}
