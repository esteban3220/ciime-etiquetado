/*
 * main.c
 * 
 * Copyright 2021 Esteban <esteban@WarMachine>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <stdio.h>
#include <gtk/gtk.h>
#include <mysql.h> 
#include <stdlib.h>

MYSQL 				*conn;
MYSQL_RES 			*res;
MYSQL_ROW 		  	row;
GtkWidget			*window;
GtkWidget			*window_login;
GtkWidget			*view_dcx2;
GtkWidget			*view_dcx1;
GtkWidget			*ety_usuario;
GtkWidget			*ety_password;
GtkWidget			*btn_sesion;
GtkWidget			*btn_impreso;
GtkWidget			*btn_revisar;
GtkWidget			*btn_etiquetado;

GtkWidget			*btn_impreso1;
GtkWidget			*btn_revisar1;
GtkWidget			*btn_etiquetado1;

GtkWidget			*btn_aceptar_1;
GtkWidget			*info_bar;
GtkWidget			*bar;
GtkLabel			*lbl_error;
GtkLabel			*lbl_hora;
GtkLabel			*lbl_hora1;
GtkLabel			*lbl_fibra;
GtkLabel			*lbl_fibra1;
GtkLabel			*lbl_info;
GtkEntry			*b_rack;
GtkEntry			*b_slot;
GtkEntry			*b_fibra;
GtkEntry			*b_unidad;
GtkEntry			*b_puerto;
GtkEntry			*b_slot_o;
GtkEntry			*b_port_o;
GtkEntry			*ety_nota;
GtkComboBoxText		*cb_status;

GtkEntry			*b_rack1;
GtkEntry			*b_slot1;
GtkEntry			*b_fibra1;
GtkEntry			*b_unidad1;
GtkEntry			*b_puerto1;
GtkEntry			*b_slot_o1;
GtkEntry			*b_port_o1;
GtkEntry			*ety_nota1;
GtkComboBoxText		*cb_status1;

GtkWidget			*dialog_error_datos;

GtkTreeIter    		iter;
GtkTreeIter    		iter2;
GtkCellRenderer     *renderer;
GtkCellRenderer     *renderer2;
GtkTreeModel        *model;
GtkTreeModel        *model2;
GtkListStore  		*store;
GtkListStore  		*store2;


GtkTreeSelection 	*select1;
GtkTreeSelection 	*select2;

GtkTreeViewColumn 	*dcx1_rack;
GtkTreeViewColumn 	*dcx1_unidad;
GtkTreeViewColumn 	*dcx1_slot;
GtkTreeViewColumn 	*dcx1_port;
GtkTreeViewColumn 	*dcx1_sloto;
GtkTreeViewColumn 	*dcx1_puertoo;
GtkTreeViewColumn 	*dcx1_nfibra;
GtkTreeViewColumn 	*dcx1_status;
GtkTreeViewColumn 	*dcx1_fecha;
GtkTreeViewColumn 	*dcx1_nota;

GtkTreeViewColumn 	*dcx2_rack;
GtkTreeViewColumn 	*dcx2_unidad;
GtkTreeViewColumn 	*dcx2_slot;
GtkTreeViewColumn 	*dcx2_port;
GtkTreeViewColumn 	*dcx2_sloto;
GtkTreeViewColumn 	*dcx2_puertoo;
GtkTreeViewColumn 	*dcx2_nfibra;
GtkTreeViewColumn 	*dcx2_status;
GtkTreeViewColumn 	*dcx2_fecha;
GtkTreeViewColumn 	*dcx2_nota;

gboolean timer_handler();
	
FILE* 			fichero;
FILE* 			fichero2;
FILE* 			fichero3;
const char 		*user;
const char 		*password;
char 			*server = "localhost";
char 			*database = "etiquetado";

enum {
  COLrack,
  COLunidad,
  COLslot,
  COLport,
  COLsloto,
  COLpuertoo,
  COLnfibra,
  COLstatus,
  COLfecha,
  COLnota,
  N_COLUMNS_DCX1
};

enum
{
  COLrack2,
  COLunidad2,
  COLslot2,
  COLport2,
  COLsloto2,
  COLpuertoo2,
  COLnfibra2,
  COLstatus2,
  COLfecha2,
  COLnota2,
  N_COLUMNS_DCX2
} ;

static GtkTreeModel * create_dcx1 (void){
	
	store = gtk_list_store_new (N_COLUMNS_DCX1, G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,
	G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
	
	gtk_list_store_append (store, &iter);
	gtk_list_store_set (store, &iter,
	COLrack,row[0],
	COLunidad,row[1],
	COLslot,row[2],
	COLport,row[3],
	COLsloto,row[4],
	COLpuertoo,row[5],
	COLnfibra,row[6],
	COLstatus,row[7],
	COLfecha,row[8],
	COLnota,row[9],-1);
	while ((row = mysql_fetch_row(res)) != NULL){
	gtk_list_store_append (store, &iter);
	gtk_list_store_set (store, &iter,COLrack,row[0],
	COLunidad,row[1],
	COLslot,row[2],
	COLport,row[3],
	COLsloto,row[4],
	COLpuertoo,row[5],
	COLnfibra,row[6],
	COLstatus,row[7],
	COLfecha,row[8],
	COLnota,row[9],-1);
}
	return GTK_TREE_MODEL (store);
}

 static GtkWidget *dcx1(void)
{	
	
	renderer = gtk_cell_renderer_text_new ();
	dcx1_rack = gtk_tree_view_column_new_with_attributes  ("Rack",renderer,"text",  COLrack,NULL);
	gtk_tree_view_append_column ( GTK_TREE_VIEW (view_dcx1),dcx1_rack);
	renderer = gtk_cell_renderer_text_new ();
	dcx1_unidad = gtk_tree_view_column_new_with_attributes ("Unidad",renderer,"text", COLunidad,NULL);
	gtk_tree_view_append_column ( GTK_TREE_VIEW (view_dcx1),dcx1_unidad);
	renderer = gtk_cell_renderer_text_new ();
	dcx1_slot = gtk_tree_view_column_new_with_attributes  ("Slot",renderer,"text", COLslot,NULL);
	gtk_tree_view_append_column ( GTK_TREE_VIEW (view_dcx1),dcx1_slot);
	renderer = gtk_cell_renderer_text_new ();
	dcx1_port = gtk_tree_view_column_new_with_attributes  ("Port",renderer,"text", COLport,NULL);
	gtk_tree_view_append_column ( GTK_TREE_VIEW (view_dcx1),dcx1_port);
	renderer = gtk_cell_renderer_text_new ();
	dcx1_sloto = gtk_tree_view_column_new_with_attributes  ("Slot Origen",renderer,"text", COLsloto,NULL);
	gtk_tree_view_append_column ( GTK_TREE_VIEW (view_dcx1),dcx1_sloto);
	renderer = gtk_cell_renderer_text_new ();
	dcx1_puertoo = gtk_tree_view_column_new_with_attributes ("Puerto Origen",renderer,"text", COLpuertoo,NULL);
	gtk_tree_view_append_column ( GTK_TREE_VIEW (view_dcx1),dcx1_puertoo);
	renderer = gtk_cell_renderer_text_new ();
	dcx1_nfibra = gtk_tree_view_column_new_with_attributes ("N. Fibra",renderer,"text", COLnfibra,NULL);
	gtk_tree_view_append_column ( GTK_TREE_VIEW (view_dcx1),dcx1_nfibra);
	renderer = gtk_cell_renderer_text_new ();
	dcx1_status = gtk_tree_view_column_new_with_attributes ("Status",renderer,"text", COLstatus,NULL);
	gtk_tree_view_append_column ( GTK_TREE_VIEW (view_dcx1),dcx1_status);
	renderer = gtk_cell_renderer_text_new ();
	dcx1_fecha = gtk_tree_view_column_new_with_attributes ("Fecha",renderer,"text", COLfecha,NULL);
	gtk_tree_view_append_column ( GTK_TREE_VIEW (view_dcx1),dcx1_fecha);
	renderer = gtk_cell_renderer_text_new ();
	dcx1_nota = gtk_tree_view_column_new_with_attributes ("Nota",renderer,"text", COLnota,NULL);
	gtk_tree_view_append_column ( GTK_TREE_VIEW (view_dcx1),dcx1_nota);
	
	model = create_dcx1();
	gtk_tree_view_set_model (GTK_TREE_VIEW (view_dcx1), model);
	g_object_unref (model);
	return view_dcx1;
}

static GtkTreeModel * create_dcx2 (void){
	
	store2 = gtk_list_store_new (N_COLUMNS_DCX2, G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,
	G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
	
	gtk_list_store_append (store2, &iter2);
	gtk_list_store_set (store2, &iter2,
	COLrack2,row[0],
	COLunidad2,row[1],
	COLslot2,row[2],
	COLport2,row[3],
	COLsloto2,row[4],
	COLpuertoo2,row[5],
	COLnfibra2,row[6],
	COLstatus2,row[7],
	COLfecha2,row[8],
	COLnota2,row[9],-1);
	while ((row = mysql_fetch_row(res)) != NULL){
	gtk_list_store_append (store2, &iter2);
	gtk_list_store_set (store2, &iter2,COLrack2,row[0],
	COLunidad2,row[1],
	COLslot2,row[2],
	COLport2,row[3],
	COLsloto2,row[4],
	COLpuertoo2,row[5],
	COLnfibra2,row[6],
	COLstatus2,row[7],
	COLfecha2,row[8],
	COLnota2,row[9],-1);
}
	return GTK_TREE_MODEL (store2);
}

 static GtkWidget *dcx2(void)
{	
	
	renderer2 = gtk_cell_renderer_text_new ();
	dcx2_rack = gtk_tree_view_column_new_with_attributes  ("Rack",renderer2,"text",  COLrack2,NULL);
	gtk_tree_view_append_column ( GTK_TREE_VIEW (view_dcx2),dcx2_rack);
	renderer2 = gtk_cell_renderer_text_new ();
	dcx2_unidad = gtk_tree_view_column_new_with_attributes ("Unidad",renderer2,"text", COLunidad2,NULL);
	gtk_tree_view_append_column ( GTK_TREE_VIEW (view_dcx2),dcx2_unidad);
	renderer2 = gtk_cell_renderer_text_new ();
	dcx2_slot = gtk_tree_view_column_new_with_attributes  ("Slot",renderer2,"text", COLslot2,NULL);
	gtk_tree_view_append_column ( GTK_TREE_VIEW (view_dcx2),dcx2_slot);
	renderer2 = gtk_cell_renderer_text_new ();
	dcx2_port = gtk_tree_view_column_new_with_attributes  ("Port",renderer2,"text", COLport2,NULL);
	gtk_tree_view_append_column ( GTK_TREE_VIEW (view_dcx2),dcx2_port);
	renderer2 = gtk_cell_renderer_text_new ();
	dcx2_sloto = gtk_tree_view_column_new_with_attributes  ("Slot Origen",renderer2,"text", COLsloto2,NULL);
	gtk_tree_view_append_column ( GTK_TREE_VIEW (view_dcx2),dcx2_sloto);
	renderer2 = gtk_cell_renderer_text_new ();
	dcx2_puertoo = gtk_tree_view_column_new_with_attributes ("Puerto Origen",renderer2,"text", COLpuertoo2,NULL);
	gtk_tree_view_append_column ( GTK_TREE_VIEW (view_dcx2),dcx2_puertoo);
	renderer2 = gtk_cell_renderer_text_new ();
	dcx2_nfibra = gtk_tree_view_column_new_with_attributes ("N. Fibra",renderer2,"text", COLnfibra2,NULL);
	gtk_tree_view_append_column ( GTK_TREE_VIEW (view_dcx2),dcx2_nfibra);
	renderer2 = gtk_cell_renderer_text_new ();
	dcx2_status = gtk_tree_view_column_new_with_attributes ("Status",renderer2,"text", COLstatus2,NULL);
	gtk_tree_view_append_column ( GTK_TREE_VIEW (view_dcx2),dcx2_status);
	renderer2 = gtk_cell_renderer_text_new ();
	dcx2_fecha = gtk_tree_view_column_new_with_attributes ("Fecha",renderer2,"text", COLfecha2,NULL);
	gtk_tree_view_append_column ( GTK_TREE_VIEW (view_dcx2),dcx2_fecha);
	renderer2 = gtk_cell_renderer_text_new ();
	dcx2_nota = gtk_tree_view_column_new_with_attributes ("Nota",renderer2,"text", COLnota2,NULL);
	gtk_tree_view_append_column ( GTK_TREE_VIEW (view_dcx2),dcx2_nota);
	
	model2 = create_dcx2();
	gtk_tree_view_set_model (GTK_TREE_VIEW (view_dcx2), model2);
	g_object_unref (model2);
	return view_dcx2;
}

void refresca_datos1(){
	
	if (gtk_tree_model_get_iter_first(model, &iter) == TRUE) {
		gtk_list_store_clear(store);
		gtk_tree_view_remove_column (GTK_TREE_VIEW(view_dcx1), dcx1_rack);
		gtk_tree_view_remove_column (GTK_TREE_VIEW(view_dcx1), dcx1_unidad);
		gtk_tree_view_remove_column (GTK_TREE_VIEW(view_dcx1), dcx1_slot);
		gtk_tree_view_remove_column (GTK_TREE_VIEW(view_dcx1), dcx1_port);
		gtk_tree_view_remove_column (GTK_TREE_VIEW(view_dcx1), dcx1_sloto);
		gtk_tree_view_remove_column (GTK_TREE_VIEW(view_dcx1), dcx1_puertoo);
		gtk_tree_view_remove_column (GTK_TREE_VIEW(view_dcx1), dcx1_nfibra);
		gtk_tree_view_remove_column (GTK_TREE_VIEW(view_dcx1), dcx1_status);
		gtk_tree_view_remove_column (GTK_TREE_VIEW(view_dcx1), dcx1_fecha);
		gtk_tree_view_remove_column (GTK_TREE_VIEW(view_dcx1), dcx1_nota);
}
}
void refresca_datos2(){
	
	if (gtk_tree_model_get_iter_first(model2, &iter2) == TRUE) {
		gtk_list_store_clear(store2);
		gtk_tree_view_remove_column (GTK_TREE_VIEW(view_dcx2), dcx2_rack);
		gtk_tree_view_remove_column (GTK_TREE_VIEW(view_dcx2), dcx2_unidad);
		gtk_tree_view_remove_column (GTK_TREE_VIEW(view_dcx2), dcx2_slot);
		gtk_tree_view_remove_column (GTK_TREE_VIEW(view_dcx2), dcx2_port);
		gtk_tree_view_remove_column (GTK_TREE_VIEW(view_dcx2), dcx2_sloto);
		gtk_tree_view_remove_column (GTK_TREE_VIEW(view_dcx2), dcx2_puertoo);
		gtk_tree_view_remove_column (GTK_TREE_VIEW(view_dcx2), dcx2_nfibra);
		gtk_tree_view_remove_column (GTK_TREE_VIEW(view_dcx2), dcx2_status);
		gtk_tree_view_remove_column (GTK_TREE_VIEW(view_dcx2), dcx2_fecha);
		gtk_tree_view_remove_column (GTK_TREE_VIEW(view_dcx2), dcx2_nota);
}
}
void consulta_dcx1(){
	user = gtk_entry_get_text(GTK_ENTRY(ety_usuario));
	password = gtk_entry_get_text(GTK_ENTRY(ety_password));
	conn = mysql_init(NULL);
 if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) 
 {
     char tempErr[60];
	 sprintf(tempErr,"%s", mysql_error(conn));
	 gtk_label_set_text(lbl_error,tempErr);
     return gtk_widget_show(dialog_error_datos);
 }else
 {
	 gtk_widget_hide_on_delete (window_login);
	 gtk_widget_show(window);	 
}
	 
 if (mysql_query(conn, "select * from DCX1")) 
 {
     char tempErr[60];
	 sprintf(tempErr,"%s", mysql_error(conn));
	 gtk_label_set_text(lbl_error,tempErr);
     return gtk_widget_show(dialog_error_datos);
 }
 res = mysql_use_result(conn); 

 while ((row = mysql_fetch_row(res)) != NULL)
						 dcx1();
 mysql_free_result(res);
 mysql_close(conn);
 
}
void consulta_dcx2(){
	user = gtk_entry_get_text(GTK_ENTRY(ety_usuario));
	password = gtk_entry_get_text(GTK_ENTRY(ety_password));
	conn = mysql_init(NULL);
 if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) 
 {
     char tempErr[60];
	 sprintf(tempErr,"%s", mysql_error(conn));
	 gtk_label_set_text(lbl_error,tempErr);
     return gtk_widget_show(dialog_error_datos);
 }
	 
 if (mysql_query(conn, "select * from DCX2")) 
 {
     char tempErr[60];
	 sprintf(tempErr,"%s", mysql_error(conn));
	 gtk_label_set_text(lbl_error,tempErr);
     return gtk_widget_show(dialog_error_datos);
 }
 res = mysql_use_result(conn); 

 while ((row = mysql_fetch_row(res)) != NULL)
						 dcx2();
 mysql_free_result(res);
 mysql_close(conn);
 
}
void busca_dcx1(){

	user = gtk_entry_get_text(GTK_ENTRY(ety_usuario));
	password = gtk_entry_get_text(GTK_ENTRY(ety_password));
	char busqueda[300];
	const char 	*consulta = gtk_entry_get_text(b_rack);
	const char 	*consulta2 = gtk_entry_get_text(b_unidad);
	const char 	*consulta3 = gtk_entry_get_text(b_slot);
	const char 	*consulta4 = gtk_entry_get_text(b_puerto);
	const char 	*consulta5 = gtk_entry_get_text(b_slot_o);
	const char 	*consulta6 = gtk_entry_get_text(b_port_o);
	const char 	*consulta7 = gtk_entry_get_text(b_fibra);
	const char 	*consulta8 = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(cb_status));
	
	if (consulta8[0]=='S'){
	sprintf(busqueda,"select * from DCX1 where Rack LIKE '%s%%' and Unidad LIKE '%s%%' and  Slot LIKE '%s%%' and Port LIKE '%s%%' and Slot_Origen LIKE '%s%%' and Puerto_Origen LIKE '%s%%' and  N_Fibra LIKE '%s%%'",consulta,consulta2,consulta3,consulta4,consulta5,consulta6,consulta7);
	}else if (consulta8[0]=='V'){
	sprintf(busqueda,"select * from DCX1 where Rack LIKE '%s%%' and Unidad LIKE '%s%%' and  Slot LIKE '%s%%' and Port LIKE '%s%%' and Slot_Origen LIKE '%s%%' and Puerto_Origen LIKE '%s%%' and  N_Fibra LIKE '%s%%' and Status IS NULL",consulta,consulta2,consulta3,consulta4,consulta5,consulta6,consulta7);
	}else {
	sprintf(busqueda,"select * from DCX1 where Rack LIKE '%s%%' and Unidad LIKE '%s%%' and  Slot LIKE '%s%%' and Port LIKE '%s%%' and Slot_Origen LIKE '%s%%' and Puerto_Origen LIKE '%s%%' and  N_Fibra LIKE '%s%%' and Status LIKE '%s%%'",consulta,consulta2,consulta3,consulta4,consulta5,consulta6,consulta7,consulta8);	
		}
	conn = mysql_init(NULL);

 if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
	{	 
	}

	if (mysql_query(conn, busqueda))
	{
		char tempErr[60];
		sprintf(tempErr,"%s", mysql_error(conn));
		gtk_label_set_text(lbl_error,tempErr);
		return gtk_widget_show(dialog_error_datos);
	}
	res = mysql_use_result(conn);
	refresca_datos1();
	while ((row = mysql_fetch_row(res)) != NULL) {
		if (gtk_tree_model_get_iter_first(model, &iter) == FALSE) {						 
						 dcx1();
						 return ;
					}	
		}
		  
	mysql_free_result(res);
	mysql_close(conn);

}

void busca_dcx2(){

	user = gtk_entry_get_text(GTK_ENTRY(ety_usuario));
	password = gtk_entry_get_text(GTK_ENTRY(ety_password));
	char busqueda[300];
	const char 	*consulta = gtk_entry_get_text(b_rack1);
	const char 	*consulta2 = gtk_entry_get_text(b_unidad1);
	const char 	*consulta3 = gtk_entry_get_text(b_slot1);
	const char 	*consulta4 = gtk_entry_get_text(b_puerto1);
	const char 	*consulta5 = gtk_entry_get_text(b_slot_o1);
	const char 	*consulta6 = gtk_entry_get_text(b_port_o1);
	const char 	*consulta7 = gtk_entry_get_text(b_fibra1);
	const char 	*consulta8 = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(cb_status1));
	
	if (consulta8[0]=='S'){
	sprintf(busqueda,"select * from DCX2 where Rack LIKE '%s%%' and Unidad LIKE '%s%%' and  Slot LIKE '%s%%' and Port LIKE '%s%%' and Slot_Origen LIKE '%s%%' and Puerto_Origen LIKE '%s%%' and  N_Fibra LIKE '%s%%'",consulta,consulta2,consulta3,consulta4,consulta5,consulta6,consulta7);
	}else if (consulta8[0]=='V'){
	sprintf(busqueda,"select * from DCX2 where Rack LIKE '%s%%' and Unidad LIKE '%s%%' and  Slot LIKE '%s%%' and Port LIKE '%s%%' and Slot_Origen LIKE '%s%%' and Puerto_Origen LIKE '%s%%' and  N_Fibra LIKE '%s%%' and Status = ''",consulta,consulta2,consulta3,consulta4,consulta5,consulta6,consulta7);
	}else {
	sprintf(busqueda,"select * from DCX2 where Rack LIKE '%s%%' and Unidad LIKE '%s%%' and  Slot LIKE '%s%%' and Port LIKE '%s%%' and Slot_Origen LIKE '%s%%' and Puerto_Origen LIKE '%s%%' and  N_Fibra LIKE '%s%%' and Status LIKE '%s%%'",consulta,consulta2,consulta3,consulta4,consulta5,consulta6,consulta7,consulta8);	
		}
	conn = mysql_init(NULL);

 if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
	{	 
	}

	if (mysql_query(conn, busqueda))
	{
		char tempErr[60];
		sprintf(tempErr,"%s", mysql_error(conn));
		gtk_label_set_text(lbl_error,tempErr);
		return gtk_widget_show(dialog_error_datos);
	}
	res = mysql_use_result(conn);
	refresca_datos2();
	while ((row = mysql_fetch_row(res)) != NULL) {
		if (gtk_tree_model_get_iter_first(model2, &iter2) == FALSE) {						 
						 dcx2();
						 return ;
					}	
		}
		  
	mysql_free_result(res);
	mysql_close(conn);

}

void inicia_sesion(){
	  consulta_dcx1();
	  consulta_dcx2();
}

void impreso(){
	user = gtk_entry_get_text(GTK_ENTRY(ety_usuario));
	password = gtk_entry_get_text(GTK_ENTRY(ety_password));
	char anadir_fac[512];
	char update[50];
	
	const char 		*nota = gtk_entry_get_text(ety_nota);
	const char 		*fibra = gtk_label_get_text(lbl_fibra);
	
	sprintf(anadir_fac,"update DCX1 set Status='Impreso', Fecha=NOW(), Nota= '%s' where N_Fibra = '%s' ",nota,fibra);
	
	conn = mysql_init(NULL);

 if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
	{	 
	}

	if (mysql_query(conn, anadir_fac))
	{
		char tempErr[60];
		sprintf(tempErr,"%s", mysql_error(conn));
		gtk_label_set_text(lbl_error,tempErr);
		return gtk_widget_show(dialog_error_datos);
	}
	res = mysql_use_result(conn);					 
	
	gtk_entry_set_text(ety_nota,"");

	mysql_free_result(res);
	mysql_close(conn);	
	sprintf(update,"Status Actualizado en %s",fibra);
	
	gtk_label_set_text(lbl_info,update);
	gtk_revealer_set_reveal_child (GTK_REVEALER (info_bar),TRUE);
	refresca_datos1();
	busca_dcx1();
	}

void etiquetado(){
	user = gtk_entry_get_text(GTK_ENTRY(ety_usuario));
	password = gtk_entry_get_text(GTK_ENTRY(ety_password));
	char anadir_fac[512];
	char update[50];
	
	const char 		*nota = gtk_entry_get_text(ety_nota);
	const char 		*fibra = gtk_label_get_text(lbl_fibra);
	
	sprintf(anadir_fac,"update DCX1 set Status='Etiquetado', Fecha=NOW(), Nota= '%s' where N_Fibra = '%s' ",nota,fibra);
	
	conn = mysql_init(NULL);

 if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
	{	 
	}

	if (mysql_query(conn, anadir_fac))
	{
		char tempErr[60];
		sprintf(tempErr,"%s", mysql_error(conn));
		gtk_label_set_text(lbl_error,tempErr);
		return gtk_widget_show(dialog_error_datos);
	}
	res = mysql_use_result(conn);					 
	
	gtk_entry_set_text(ety_nota,"");

	mysql_free_result(res);
	mysql_close(conn);	
	sprintf(update,"Status Actualizado en %s",fibra);
	
	gtk_label_set_text(lbl_info,update);
	gtk_revealer_set_reveal_child (GTK_REVEALER (info_bar),TRUE);
	refresca_datos1();
	busca_dcx1();
}

void revisar(){
	user = gtk_entry_get_text(GTK_ENTRY(ety_usuario));
	password = gtk_entry_get_text(GTK_ENTRY(ety_password));
	char anadir_fac[512];
	char update[50];
	
	const char 		*nota = gtk_entry_get_text(ety_nota);
	const char 		*fibra = gtk_label_get_text(lbl_fibra);
	
	sprintf(anadir_fac,"update DCX1 set Status='Revisar', Fecha=NOW(), Nota= '%s' where N_Fibra = '%s' ",nota,fibra);
	
	conn = mysql_init(NULL);

 if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
	{	 
	}

	if (mysql_query(conn, anadir_fac))
	{
		char tempErr[60];
		sprintf(tempErr,"%s", mysql_error(conn));
		gtk_label_set_text(lbl_error,tempErr);
		return gtk_widget_show(dialog_error_datos);
	}
	res = mysql_use_result(conn);	
	gtk_entry_set_text(ety_nota,"");

	mysql_free_result(res);
	mysql_close(conn);	
	sprintf(update,"Status Actualizado en %s",fibra);
	
	gtk_label_set_text(lbl_info,update);
	gtk_revealer_set_reveal_child (GTK_REVEALER (info_bar),TRUE);
	refresca_datos1();
	busca_dcx1();
}



void impreso2(){
	user = gtk_entry_get_text(GTK_ENTRY(ety_usuario));
	password = gtk_entry_get_text(GTK_ENTRY(ety_password));
	char anadir_fac[512];
	char update[50];
	
	const char 		*nota = gtk_entry_get_text(ety_nota1);
	const char 		*fibra = gtk_label_get_text(lbl_fibra1);
	
	sprintf(anadir_fac,"update DCX2 set Status='Impreso', Fecha=NOW(), Nota= '%s' where N_Fibra = '%s' ",nota,fibra);
	
	conn = mysql_init(NULL);

 if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
	{	 
	}

	if (mysql_query(conn, anadir_fac))
	{
		char tempErr[60];
		sprintf(tempErr,"%s", mysql_error(conn));
		gtk_label_set_text(lbl_error,tempErr);
		return gtk_widget_show(dialog_error_datos);
	}
	res = mysql_use_result(conn);					 
	
	gtk_entry_set_text(ety_nota1,"");

	mysql_free_result(res);
	mysql_close(conn);	
	sprintf(update,"Status Actualizado en %s",fibra);
	
	gtk_label_set_text(lbl_info,update);
	gtk_revealer_set_reveal_child (GTK_REVEALER (info_bar),TRUE);
	refresca_datos2();
	busca_dcx2();
	}

void etiquetado2(){
	user = gtk_entry_get_text(GTK_ENTRY(ety_usuario));
	password = gtk_entry_get_text(GTK_ENTRY(ety_password));
	char anadir_fac[512];
	char update[50];
	
	const char 		*nota = gtk_entry_get_text(ety_nota1);
	const char 		*fibra = gtk_label_get_text(lbl_fibra1);
	
	sprintf(anadir_fac,"update DCX2 set Status='Etiquetado', Fecha=NOW(), Nota= '%s' where N_Fibra = '%s' ",nota,fibra);
	
	conn = mysql_init(NULL);

 if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
	{	 
	}

	if (mysql_query(conn, anadir_fac))
	{
		char tempErr[60];
		sprintf(tempErr,"%s", mysql_error(conn));
		gtk_label_set_text(lbl_error,tempErr);
		return gtk_widget_show(dialog_error_datos);
	}
	res = mysql_use_result(conn);					 
	
	gtk_entry_set_text(ety_nota1,"");

	mysql_free_result(res);
	mysql_close(conn);	
	sprintf(update,"Status Actualizado en %s",fibra);
	
	gtk_label_set_text(lbl_info,update);
	gtk_revealer_set_reveal_child (GTK_REVEALER (info_bar),TRUE);
	refresca_datos2();
	busca_dcx2();
}

void revisar2(){
	user = gtk_entry_get_text(GTK_ENTRY(ety_usuario));
	password = gtk_entry_get_text(GTK_ENTRY(ety_password));
	char anadir_fac[512];
	char update[50];
	
	const char 		*nota = gtk_entry_get_text(ety_nota1);
	const char 		*fibra = gtk_label_get_text(lbl_fibra1);
	
	sprintf(anadir_fac,"update DCX2 set Status='Revisar', Fecha=NOW(), Nota= '%s' where N_Fibra = '%s' ",nota,fibra);
	
	conn = mysql_init(NULL);

 if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
	{	 
	}

	if (mysql_query(conn, anadir_fac))
	{
		char tempErr[60];
		sprintf(tempErr,"%s", mysql_error(conn));
		gtk_label_set_text(lbl_error,tempErr);
		return gtk_widget_show(dialog_error_datos);
	}
	res = mysql_use_result(conn);	
	gtk_entry_set_text(ety_nota1,"");

	mysql_free_result(res);
	mysql_close(conn);	
	sprintf(update,"Status Actualizado en %s",fibra);
	
	gtk_label_set_text(lbl_info,update);
	gtk_revealer_set_reveal_child (GTK_REVEALER (info_bar),TRUE);
	refresca_datos2();
	busca_dcx2();
}
void on_info_close(){
	gtk_label_set_text(lbl_info,"");
	gtk_revealer_set_reveal_child (GTK_REVEALER (info_bar),FALSE);
	}

/*
void on_exportar_pdf_clicked(){
	const char *tabla = gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(tabla_items));
	char exporta [40];
	sprintf(exporta,"select * from %s",tabla);
	
	const char cabeceras []="\\documentclass[a4paper,6pt]{report}\n\\usepackage[T1]{fontenc}\n \\usepackage[utf8]{inputenc}\n\\usepackage{lmodern}\n\\usepackage[spanish]{babel}\n\\usepackage{pdflscape}\n";
	char init_document [] = "\\begin{document}\n\\begin{landscape}\n \\setlength{\\textwidth}{10mm}\n\\setlength{\\textheight}{10mm}\n \\setlength{\\oddsidemargin}{-70mm} \n\\setlength{\\evensidemargin}{100mm}\n\\setlength{\\topmargin}{35mm}\n";
	char campos [] = "ID & ID Pro. Ant. & Nombre Ant. & Direccion Ant. & Tel. Ant. & Region Ant. & Pais Ant. & RFC Ant. & Correo Ant. & ID Pro. New & Nombre New & Direcc. New & Telefono New & Region New & Pais New & RFC New & Correo New & User & Modificado & Accion & Id Empresa\\\\ \\hline \\hline\n";
	char campos2 [] = "ID & ID Pro. Ant. & ID Emp. Ant. & Fecha Ven. Ant. & Can. Ant. & Precio Ant. & M.Pago Ant. & Desc. Ant. & Total Ant. & ID Pro. New & ID Emp New & F. Ven. New & Cant. New & Precio New & MPago New & Desc. New & Total New & User & Modificado & Accion & Id Fac.\\\\ \\hline \\hline\n";
	char campos3 [] = "ID & Nombre Ant. & Marca Ant. & FCaducidad Ant. & FProduccion Ant. & Num. Lote Ant. & Desc. Ant. & CBarra Ant. & Con. Neto Ant. & Nombre New & Marca New & FCaducidad New & FProd. New & Num. Lote New & Desc. New & CBarra New & Con. Neto & User & Modificado & Accion & Id Pro.\\\\ \\hline \\hline\n";

	char inicia_tabla [] = "\\begin{table}\n\\label{tab:}\n\\begin{center}\n \\resizebox{27cm}{!} { \n\\begin{tabular}{| c | c | c | c | c | c | c | c | c | c | c | c | c | c | c | c | c | c | c | c | c | }\n";
	char fin_tabla [] = "\\end{tabular}\n }\\end{center}\n\\end{table}\n";
	char fin_documento [] = "\n\\end{landscape}\n\\end{document}";
	char hline[]= "\\hline\n";

	user = gtk_entry_get_text(g_Entry_Usuario);
	password = gtk_entry_get_text(g_Entry_Contrasena);
	
	conn = mysql_init(NULL);

 if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
	{	 
	}

	if (mysql_query(conn, exporta))
	{
		char tempErr[60];
		sprintf(tempErr,"%s", mysql_error(conn));
		gtk_label_set_text(lbl_error,tempErr);
		return gtk_widget_show(dialog_error_datos);
	}
	res = mysql_use_result(conn);
	
//==========================================================================================================================================================		
	if(tabla[10]== 'e'){
		fichero = fopen("Empresa.tex", "wt");
	fputs(cabeceras, fichero);
	fputs(init_document, fichero);
	fputs(inicia_tabla, fichero);
	fputs(hline,fichero);
	fputs(campos, fichero);
	while ((row = mysql_fetch_row(res)) != NULL) {
		fprintf(fichero,"%s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s \\\\ \\hline\n",row[0],row[1],row[2],row[3],row[4],row[5],row[6],row[7],row[8],row[9],row[10],row[11],row[12],row[13],row[14],row[15],row[16],row[17],row[18],row[19],row[20]);
	}
	fputs(hline,fichero);
	fputs(fin_tabla,fichero);
	fputs(fin_documento, fichero);
	fclose(fichero); 
	system("latexmk -pdf -synctex=1 Empresa.tex ");
    system("evince Empresa.pdf &");
    //return ;
//==========================================================================================================================================================    
	}else if(tabla[10]== 'f'){
	fichero2 = fopen("Factura.tex", "wt");
	fputs(cabeceras, fichero2);
	fputs(init_document, fichero2);
	fputs(inicia_tabla, fichero2);
	fputs(hline,fichero2);
	fputs(campos2, fichero2);
	while ((row = mysql_fetch_row(res)) != NULL) {
		fprintf(fichero2,"%s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s \\\\ \\hline\n",row[0],row[1],row[2],row[3],row[4],row[5],row[6],row[7],row[8],row[9],row[10],row[11],row[12],row[13],row[14],row[15],row[16],row[17],row[18],row[19],row[20]);
	}
	fputs(hline,fichero2);
	fputs(fin_tabla,fichero2);
	fputs(fin_documento, fichero2);
	fclose(fichero2); 
	system("latexmk -pdf -synctex=1 Factura.tex ");
    system("evince Factura.pdf &");
   // return ;
//==========================================================================================================================================================   
		}else if(tabla[10]== 'p'){
	fichero3 = fopen("Producto.tex", "wt");
	fputs(cabeceras, fichero3);
	fputs(init_document, fichero3);
	fputs(inicia_tabla, fichero3);
	fputs(hline,fichero3);
	fputs(campos3, fichero3);
	while ((row = mysql_fetch_row(res)) != NULL) {
		fprintf(fichero3,"%s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s \\\\ \\hline\n",row[0],row[1],row[2],row[3],row[4],row[5],row[6],row[7],row[8],row[9],row[10],row[11],row[12],row[13],row[14],row[15],row[16],row[17],row[18],row[19],row[20]);
	}
	fputs(hline,fichero3);
	fputs(fin_tabla,fichero3);
	fputs(fin_documento, fichero3);
	fclose(fichero3); 
	system("latexmk -pdf -synctex=1 Producto.tex ");
    system("evince Producto.pdf &");
    //return ;
}
//==========================================================================================================================================================
	mysql_free_result(res);
	mysql_close(conn);
  

    gtk_label_set_text(lbl_info,"PDF Creado");
	gtk_revealer_set_reveal_child (GTK_REVEALER (info_bar),TRUE);
	}

 */
 void oculta1(){
	gtk_widget_hide(dialog_error_datos);
	}

void tree_selection_changed_cb(GtkTreeSelection *selection, gpointer data){
        gchar *author;

        if (gtk_tree_selection_get_selected (selection, &model, &iter))
        {
                gtk_tree_model_get (model, &iter, COLnfibra, &author, -1);
                gtk_label_set_text(lbl_fibra,author);
        }	
	}
void tree_selection_changed_cb2(GtkTreeSelection *selection2, gpointer data){
        gchar *author;

        if (gtk_tree_selection_get_selected (selection2, &model2, &iter2))
        {
                gtk_tree_model_get (model2, &iter2, COLnfibra2, &author, -1);
                gtk_label_set_text(lbl_fibra1,author);
        }	
	}
void on_Window_BD_destroy(){
	 gtk_main_quit();
	}
int main(int argc, char *argv[])
	{
		GtkBuilder      	*builder; 
		gtk_init(&argc, &argv);

		builder = gtk_builder_new();
		gtk_builder_add_from_file (builder, "etiquetado.glade", NULL);
		window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
		window_login = GTK_WIDGET(gtk_builder_get_object(builder, "window_login"));
		view_dcx2 = GTK_WIDGET(gtk_builder_get_object(builder, "view_dcx2"));
		view_dcx1 = GTK_WIDGET(gtk_builder_get_object(builder, "view_dcx1"));
		ety_usuario = GTK_WIDGET(gtk_builder_get_object(builder, "ety_usuario"));
		ety_password = GTK_WIDGET(gtk_builder_get_object(builder, "ety_password"));
		ety_nota = GTK_ENTRY(gtk_builder_get_object(builder, "ety_nota"));
		ety_nota1 = GTK_ENTRY(gtk_builder_get_object(builder, "ety_nota1"));
		btn_sesion = GTK_WIDGET(gtk_builder_get_object(builder, "btn_sesion"));
		btn_aceptar_1 = GTK_WIDGET(gtk_builder_get_object(builder, "btn_aceptar_1"));
		info_bar = GTK_WIDGET(gtk_builder_get_object(builder, "info_bar"));
		lbl_error = GTK_LABEL(gtk_builder_get_object(builder, "lbl_error"));
		lbl_hora = GTK_LABEL(gtk_builder_get_object(builder, "lbl_hora"));
		lbl_hora1 = GTK_LABEL(gtk_builder_get_object(builder, "lbl_hora1"));
		lbl_fibra = GTK_LABEL(gtk_builder_get_object(builder, "lbl_fibra"));
		lbl_fibra1 = GTK_LABEL(gtk_builder_get_object(builder, "lbl_fibra1"));
		lbl_info = GTK_LABEL(gtk_builder_get_object(builder, "lbl_info"));
		dialog_error_datos = GTK_WIDGET(gtk_builder_get_object(builder, "dialog_error_datos"));
		b_rack = GTK_ENTRY(gtk_builder_get_object(builder, "b_rack"));
		b_unidad = GTK_ENTRY(gtk_builder_get_object(builder, "b_unidad"));
		b_puerto = GTK_ENTRY(gtk_builder_get_object(builder, "b_puerto"));
		b_port_o = GTK_ENTRY(gtk_builder_get_object(builder, "b_port_o"));
		b_slot_o = GTK_ENTRY(gtk_builder_get_object(builder, "b_slot_o"));
		b_slot = GTK_ENTRY(gtk_builder_get_object(builder, "b_slot"));
		b_fibra = GTK_ENTRY(gtk_builder_get_object(builder, "b_fibra"));
		cb_status = GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "cb_status"));
		btn_etiquetado = GTK_WIDGET(gtk_builder_get_object(builder, "btn_etiquetado"));
		btn_impreso = GTK_WIDGET(gtk_builder_get_object(builder, "btn_impreso"));
		btn_revisar = GTK_WIDGET(gtk_builder_get_object(builder, "btn_revisar"));
		
		b_rack1 = GTK_ENTRY(gtk_builder_get_object(builder, "b_rack1"));
		b_unidad1 = GTK_ENTRY(gtk_builder_get_object(builder, "b_unidad1"));
		b_puerto1 = GTK_ENTRY(gtk_builder_get_object(builder, "b_puerto1"));
		b_port_o1 = GTK_ENTRY(gtk_builder_get_object(builder, "b_port_o1"));
		b_slot_o1 = GTK_ENTRY(gtk_builder_get_object(builder, "b_slot_o1"));
		b_slot1 = GTK_ENTRY(gtk_builder_get_object(builder, "b_slot1"));
		b_fibra1 = GTK_ENTRY(gtk_builder_get_object(builder, "b_fibra1"));
		cb_status1 = GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "cb_status1"));
		btn_etiquetado1 = GTK_WIDGET(gtk_builder_get_object(builder, "btn_etiquetado1"));
		btn_impreso1 = GTK_WIDGET(gtk_builder_get_object(builder, "btn_impreso1"));
		btn_revisar1 = GTK_WIDGET(gtk_builder_get_object(builder, "btn_revisar1"));
		
		bar = GTK_WIDGET(gtk_builder_get_object(builder, "bar"));
		
		select1 = gtk_tree_view_get_selection (GTK_TREE_VIEW (view_dcx1));
		gtk_tree_selection_set_mode (select1, GTK_SELECTION_SINGLE);
		select2 = gtk_tree_view_get_selection (GTK_TREE_VIEW (view_dcx2));
		gtk_tree_selection_set_mode (select2, GTK_SELECTION_SINGLE);
		
		g_signal_connect(G_OBJECT(ety_password),"activate",G_CALLBACK(inicia_sesion),NULL);
		g_signal_connect(G_OBJECT(btn_aceptar_1),"clicked",G_CALLBACK(oculta1),NULL);
		g_signal_connect(G_OBJECT(btn_sesion),"clicked",G_CALLBACK(inicia_sesion),NULL);
		g_signal_connect(G_OBJECT(bar),"response",G_CALLBACK(on_info_close),NULL);
		
		g_signal_connect(G_OBJECT(b_rack),"changed",G_CALLBACK(busca_dcx1),NULL);
		g_signal_connect(G_OBJECT(b_slot),"changed",G_CALLBACK(busca_dcx1),NULL);
		g_signal_connect(G_OBJECT(b_fibra),"changed",G_CALLBACK(busca_dcx1),NULL);
		g_signal_connect(G_OBJECT(cb_status),"changed",G_CALLBACK(busca_dcx1),NULL);	
		g_signal_connect(G_OBJECT(b_unidad),"changed",G_CALLBACK(busca_dcx1),NULL);
		g_signal_connect(G_OBJECT(b_puerto),"changed",G_CALLBACK(busca_dcx1),NULL);
		g_signal_connect(G_OBJECT(b_port_o),"changed",G_CALLBACK(busca_dcx1),NULL);
		g_signal_connect(G_OBJECT(b_slot_o),"changed",G_CALLBACK(busca_dcx1),NULL);
		
		g_signal_connect(G_OBJECT(btn_etiquetado),"clicked",G_CALLBACK(etiquetado),NULL);
		g_signal_connect(G_OBJECT(btn_revisar),"clicked",G_CALLBACK(revisar),NULL);
		g_signal_connect(G_OBJECT(btn_impreso),"clicked",G_CALLBACK(impreso),NULL);
		
		g_signal_connect(G_OBJECT(select1),"changed",G_CALLBACK (tree_selection_changed_cb),NULL);	
		

		g_signal_connect(G_OBJECT(b_rack1),"changed",G_CALLBACK(busca_dcx2),NULL);
		g_signal_connect(G_OBJECT(b_slot1),"changed",G_CALLBACK(busca_dcx2),NULL);
		g_signal_connect(G_OBJECT(b_fibra1),"changed",G_CALLBACK(busca_dcx2),NULL);
		g_signal_connect(G_OBJECT(cb_status1),"changed",G_CALLBACK(busca_dcx2),NULL);	
		g_signal_connect(G_OBJECT(b_unidad1),"changed",G_CALLBACK(busca_dcx2),NULL);
		g_signal_connect(G_OBJECT(b_puerto1),"changed",G_CALLBACK(busca_dcx2),NULL);
		g_signal_connect(G_OBJECT(b_port_o1),"changed",G_CALLBACK(busca_dcx2),NULL);
		g_signal_connect(G_OBJECT(b_slot_o1),"changed",G_CALLBACK(busca_dcx2),NULL);
		
		g_signal_connect(G_OBJECT(btn_etiquetado1),"clicked",G_CALLBACK(etiquetado2),NULL);
		g_signal_connect(G_OBJECT(btn_revisar1),"clicked",G_CALLBACK(revisar2),NULL);
		g_signal_connect(G_OBJECT(btn_impreso1),"clicked",G_CALLBACK(impreso2),NULL);
		g_signal_connect(G_OBJECT(select2),"changed",G_CALLBACK (tree_selection_changed_cb2),NULL);	
		g_signal_connect(G_OBJECT(window_login),"delete-event",G_CALLBACK(on_Window_BD_destroy),NULL);
		g_signal_connect(G_OBJECT(window),"delete-event",G_CALLBACK(on_Window_BD_destroy),NULL);
			
		
		gtk_builder_connect_signals(builder, NULL);
		g_timeout_add_seconds(1, (GSourceFunc)timer_handler, NULL);
		gtk_widget_show(window_login);
		gtk_main();			
		
	}
gboolean timer_handler()
{
    GDateTime *date_time;
    gchar *dt_format;

    date_time = g_date_time_new_now_local();                        // get local time
    dt_format = g_date_time_format(date_time, "%d/%m/%y %H:%M:%S");            // 24hr time format
    gtk_label_set_text(lbl_hora, dt_format);
    gtk_label_set_text(lbl_hora1, dt_format);    // update label
    g_free (dt_format);
    
    return TRUE;
}


