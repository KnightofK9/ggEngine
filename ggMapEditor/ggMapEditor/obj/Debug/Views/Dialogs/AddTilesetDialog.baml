   M S B A M L   `   `   `  ����F  BggMapEditor, Version=1.0.0.0, Culture=neutral, PublicKeyToken=nullE'clr-namespace:ggMapEditor.Views.DialogsggMapEditor.Views.Dialogs  5   	   ?$clr-namespace:ggMapEditor.ViewModelsggMapEditor.ViewModels  5   	   9!clr-namespace:ggMapEditor.HelpersggMapEditor.Helpers  5   	   0    *ggMapEditor.Views.Dialogs.AddTilesetDialog   5   	   W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35^ ZWindowsFormsIntegration, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35F 9http://schemas.microsoft.com/winfx/2006/xaml/presentation     5   	   R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5   	   @d2http://schemas.microsoft.com/expression/blend/2008     5   	   Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5   	   9local'clr-namespace:ggMapEditor.Views.Dialogs     5   	   3vm$clr-namespace:ggMapEditor.ViewModels     5   	   5helpers!clr-namespace:ggMapEditor.Helpers     5   	     � Title$  
AddTileSet��5
   	   $	��300��6   $	��300��6)   &    ggMapEditor.Helpers.DialogCloser   DialogResult 5   	   �� *CloseWindowFlag+.��5      �  � RowDefinitions 5   
   �� 5      $��* �6   �� 5      $��* �6   �� 5      $
��auto �6   .+�5   
   �� $��0��6   $��Tileset��5      .��5      ��  �� Orientation$ Vertical=�6   .+�5      ]� $��5q�6   .+�5      �� $
��Left=�6    $
��Name��5       $��0,0,10,0q�5       �� 5      $
��Left=�6   
���������5      �� *Name+5      ]� 5!      $��5q�6   .+�5"      �� $
��Left=�6    $
��Type��5#       $��0,0,10,0q�5$       �� 5%      -   5        $��	comboType��5%      .@�5&      �� 
 � Tag$
 Base��6'   .��62   Based on Tileset Image5(      �� 5)      $ 
Collection��6'   .��68   Collection of Images5+      5,      5-      5.      5/      �� 50   
   $��1��6   $��Image��51      $��2��6"   .��52      �� $ Vertical=�6   .+�53      ]� $��5q�6   .+�54      �� $
��Left=�6    $��Source��55       $��0,0,10,0q�56       �� 57      -   5        $��tbImagePath��57       $
��Left=�59       
�������$	��150��5;       ��58       �� *
ImageUri+5;       �� 5<      $
��Left=�6   $��	Browse...��5=      $��10,0,0,0q�5>      ��5?      �� *OpenFileCommand+5@      ]� 5A      $��5q�6   $
��Left=�5B      .+�5C      �� $
��Left=�6    $��	Tile size��5D       $��0,0,10,0q�5E       �� 5F      -   5        $��
tbTileSize��5F      $
��Left=�5G      
�������$��30��5J      ��5I      �� *
TileSize+5J      5K      5L      5M      �� 5O   
   $��5��6   $ 
Horizontal=�5P      $��Right=�5Q      $��30��5R      $��5q�5S      .+�5T      �� $��OK��6   $��60��5U      $��0,0,10,0q�5V      ��5W      �� *	OkCommand+�� 5X      $��Cancel��6   $��60��5Y      ��5Z      �� *CancelCommand+5[      5\      5]      