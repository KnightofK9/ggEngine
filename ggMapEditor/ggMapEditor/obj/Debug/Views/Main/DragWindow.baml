   M S B A M L   `   `   `  ����F  BggMapEditor, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null?$clr-namespace:ggMapEditor.Views.MainggMapEditor.Views.Main  5   	   G(clr-namespace:ggMapEditor.Views.ControlsggMapEditor.Views.Controls  5   	   '    !ggMapEditor.Views.Main.DragWindow   5   	   W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35^ ZWindowsFormsIntegration, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35F 9http://schemas.microsoft.com/winfx/2006/xaml/presentation     5   	   R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5   	   @d2http://schemas.microsoft.com/expression/blend/2008     5   	   Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5   	   6local$clr-namespace:ggMapEditor.Views.Main     5   	   9ctrl(clr-namespace:ggMapEditor.Views.Controls     5   	     � Title$  
DragWindow��5	   	   $	��500��6   $	��500��6)   .��5
      �  � ColumnDefinitions 5   
   �� 5      $��* �6   �� 5      $��* �6   .+�5   
   (   "ggMapEditor.Views.Controls.ZoomBox  -   5          Name$ zoomBox��5      $��Stretch=�5      $��Stretch=�5         Children. 5      +   %ggMapEditor.Views.Controls.MatrixGrid  $
��Left=�6   $	��Top=�5         RowCount$ 10��5         ColumnCount$ 20��5         TileSize$ 32��5      5      � 5   
   -   5        $
��grid��5      $��1��5       � RowDefinitions 5      �� 5      $��* �6    �� 5      $��* �6    .+�5      %   ggMapEditor.Views.Controls.Tile     
TileHeight$ 32Q�6   	   	TileWidth$	 32Q�5       
   
TileSource$&
  pack://application:,,,/rampo.jpg��5!      5"      5#      5$      