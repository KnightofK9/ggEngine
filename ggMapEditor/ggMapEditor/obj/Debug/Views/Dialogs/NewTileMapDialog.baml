   M S B A M L   `   `   `  ����F  BggMapEditor, Version=1.0.0.0, Culture=neutral, PublicKeyToken=nullE'clr-namespace:ggMapEditor.Views.DialogsggMapEditor.Views.Dialogs  5   	   9!clr-namespace:ggMapEditor.HelpersggMapEditor.Helpers  5   	   0    *ggMapEditor.Views.Dialogs.NewTileMapDialog   5   	   W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35^ ZWindowsFormsIntegration, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35F 9http://schemas.microsoft.com/winfx/2006/xaml/presentation     5   	   R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5   	   @d2http://schemas.microsoft.com/expression/blend/2008     5   	   Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5   	   9local'clr-namespace:ggMapEditor.Views.Dialogs     5   	   5helpers!clr-namespace:ggMapEditor.Helpers     5   	     � WindowStartupLocation$  CenterScreen=�5	   	    � 
ResizeMode$ NoResize=�5
   	    � SizeToContent$ WidthAndHeight=�5   	    � Title$ New Tile Map��5   	   &    ggMapEditor.Helpers.DialogCloser   DialogResult 5   	   �� *CloseWindowFlag+.��5      � $��10q�6   .+�5   
   ��  �� Orientation$ Vertical=�6   $��Center=�5      $��Center=�5      .+�5      �� $ 
Horizontal=�6   .+�5      �� $��Name:��6   $��0,0,15,0q�5      �� 5      $	��100��5      ��5      �� *
FolderName+ �� Mode$ TwoWay=�5      5      �� 5      $��20��6   �� 5      $ 
Horizontal=�6   .+�5      �� $��	Map size:��6   $��0,0,15,0q�5      �� 5      $��50��5      ��5      �� *
RowCount+$ TwoWay=�5      �� 5      $��x��6   $
��10,0q�5       �� 5!      $��50��5"      ��5!      �� *ColumnCount+$ TwoWay=�5"      �� 5#      $��Tiles��6   $	��5,0q�5$      5%      �� 5'      $��20��6   �� 5)      $ 
Horizontal=�6   .+�5*      �� $��
Tile size:��6   $��0,0,15,0q�5+      �� 5,      $��50��5-      ��5,      �� *
TileSize+$ TwoWay=�5-      5.      �� 50      $��10��6   �� 52      ��6   �� *	MapPixels+$ OneWay=��� 54      $ Vertical=�6   .+�55      ]� $��5q�6   .+�56      �� $
��Left=�6    $
��Path��57       $��0,0,10,0q�58       �� 59      -   5        $��tbFolderPath��59       $
��Left=�5;       
�������$	��150��5=       ��5:       �� *
FolderPath+5=       �� 5>      $
��Left=�6   $��	Browse...��5?      $��10,0,0,0q�5@      ��5A      �� *BrowseCommand+5B      5C      �� 5E      $ 
Horizontal=�6   $��Right=�5F      $��0,20,0,0q�5G      .+�5H      �� $��OK��6   $��60��5I      $��0,0,10,0q�5J      ��5K      �� *	OkCommand+�� 5L      $��Cancel��6   $��60��5M      ��5N      �� *CancelCommand+5O      5P      5Q      5R      