void psptest::tools_pressed()
{
   hide_widgets( menu_widgets );
   menu_button->setPixmap( id_to_icon[ "tools" ] );
   delete_widgets_layouts( panel1_widgets, panel1_layouts );
   delete_widgets_layouts( panel1_sub_widgets, panel1_sub_layouts );
   panel1_widget_map.clear();
   panel1_inputs.clear();
   panel1_outputs.clear();
   panel1_map_input.clear();

   QHBoxLayout *hbl = new QHBoxLayout( 0 );

   {
      mQPushButton * pb = new mQPushButton( this );
      pb->setText( "Center" );
      pb->setMaximumHeight( 60 );
      pb->show();
      // this is supposed to automatically disconnect on deletion of the widget
      connect( pb, SIGNAL( clicked() ), SLOT( module_load_tools_center() ) );
      if ( panel1_widgets.size() )
      {
         hbl->addSpacing( 2 );
      }
      hbl->addWidget( pb );
      panel1_widgets.push_back( pb );
   }
   {
      mQPushButton * pb = new mQPushButton( this );
      pb->setText( "Align" );
      pb->setMaximumHeight( 60 );
      pb->show();
      // this is supposed to automatically disconnect on deletion of the widget
      connect( pb, SIGNAL( clicked() ), SLOT( module_load_tools_align() ) );
      if ( panel1_widgets.size() )
      {
         hbl->addSpacing( 2 );
      }
      hbl->addWidget( pb );
      panel1_widgets.push_back( pb );
   }
   {
      mQPushButton * pb = new mQPushButton( this );
      pb->setText( "Filetest" );
      pb->setMaximumHeight( 60 );
      pb->show();
      // this is supposed to automatically disconnect on deletion of the widget
      connect( pb, SIGNAL( clicked() ), SLOT( module_load_tools_filetest() ) );
      if ( panel1_widgets.size() )
      {
         hbl->addSpacing( 2 );
      }
      hbl->addWidget( pb );
      panel1_widgets.push_back( pb );
   }
   {
      mQPushButton * pb = new mQPushButton( this );
      pb->setText( "Data Interpolation" );
      pb->setMaximumHeight( 60 );
      pb->show();
      // this is supposed to automatically disconnect on deletion of the widget
      connect( pb, SIGNAL( clicked() ), SLOT( module_load_tools_data_interpolation() ) );
      if ( panel1_widgets.size() )
      {
         hbl->addSpacing( 2 );
      }
      hbl->addWidget( pb );
      panel1_widgets.push_back( pb );
   }
   {
      QLabel * lbl = new QLabel( "", this );
      gl_panel1->addWidget( lbl, 3, 0 );
      panel1_widgets.push_back( lbl );
   }

   gl_panel1->addLayout( hbl, 0, 1 );
   panel1_layouts.push_back( hbl );
   gl_panel1->setColumnStretch( 0, 1 );
   gl_panel1->setColumnStretch( 1, 0 );
   gl_panel1->setColumnStretch( 2, 1 );
   gl_panel1->setRowStretch( 0, 0 );
   gl_panel1->setRowStretch( 1, 0 );
   gl_panel1->setRowStretch( 2, 0 );
   gl_panel1->setRowStretch( 3, 1 );
}
