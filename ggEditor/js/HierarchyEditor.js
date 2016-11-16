/**
 * Created by Knight of k9 on 12/11/2016.
 */
var HierarchyEditor = function () {
    var hierarchyPanel = $("#gg-info-hierarchy");
    var navTab = $("#gg-info-hierarchy-nav-tab");
    var hierarchyListPanel = $("#gg-hierarchy-list");
    //<a href="#" class="list-group-item">Item 1</a>
    //<div class="list-group">

    var hierarchyList = [];
    var hObjectList = [];
    var id = 0;
    this.setActive = function(isActive){
        if(isActive){
            hierarchyPanel.css("display","block");
            navTab.addClass("active");
        }else{
            hierarchyPanel.css("display","none");
            navTab.removeClass("active");
        }

    };
    this.clearAll = function(){
        hierarchyListPanel.html("");
        hierarchyList = [];
        hObjectList = [];
        id = 0;
    };
    this.addObjectToHierarchy = function (name, object) {
        var hierarchyObject = new HierarchyObject();
        hierarchyObject.id = id++;
        hierarchyObject.name = name;
        hierarchyObject.item = object;
        hierarchyList.push(hierarchyObject);
        hObjectList.push(hierarchyObject);
        return hierarchyObject;
    };
    this.addObjectToHObject = function(name, object,hParent){
        var hierarchyObject = new HierarchyObject();
        hierarchyObject.id = id++;
        hierarchyObject.name = name;
        hierarchyObject.item = object;
        hierarchyObject.parent = hParent;
        hObjectList.push(hierarchyObject);
        hParent.childList.push(hierarchyObject);
    };
    this.removeHObjectFromHObject = function(hObject, hParent){
        for(var i  = 0;i>hParent.childList.length;i++){
            var childHObject = hParent.childList[i];
            if(childHObject.id === hObject.id){
                hParent.childList.splice(i,1);
                break;
            }
        }
    };
    this.removeObjectFromHObject = function(name, hParent){
        for(var i  = 0;i>hParent.childList.length;i++){
            var childHObject = hParent.childList[i];
            if(childHObject.name === name){
                hParent.childList.splice(i,1);
                break;
            }
        }
    };

    this.removeAllObjectFromHObject = function(name, hParent){
        for(var i  = 0;i>hParent.childList.length;i++){
            var childHObject = hParent.childList[i];
            if(childHObject.name === name){
                hParent.childList.splice(i,1);
            }
        }
    };
    this.removeObject = function (name, object) {

    };
    this.removeAllObject = function () {
        while(hierarchyList.length){
            hierarchyList.pop();
        }
    };
    this.updateHierarchy = function () {
        reloadHierarchy();
    };

    this.handleRemoveClick = function(hObjectId){
        for(var i = 0;i<hObjectList.length; i++){
            if(hObjectList[i].id === hObjectId){
                if(!hObjectList[i].item.callDestroy()) return;
                if(hObjectList[i].parent != null){
                    for(var t = 0;t<hObjectList[i].parent.childList.length;t++){
                        if(hObjectList[i].parent.childList[t].id === hObjectId){
                            hObjectList[i].parent.childList.splice(t,1);
                            break;
                        }
                    }
                }
                hObjectList.splice(i,1);
                break;
            }
        }
        reloadHierarchy();
    };

    /**
     * Private function
     */


    var reloadHierarchy = function () {
        hierarchyListPanel.html("");
        var div = "";
        for (var i = 0; i < hierarchyList.length; i++) {
            div += createHierarchyDiv(hierarchyList[i]);
        }
        hierarchyListPanel.html(div);
    };

    var createHierarchyDiv = function (hObject) {
        var div = createLine(hObject.id, hObject.name);
        for(var i = 0;i<hObject.childList.length;i++){
            div += createChild(createHierarchyDiv(hObject.childList[i]));
        }
        return div;
    };

    var createLine = function (id, name) {
        return '<a  class="list-group-item">' + name
            +'<i onclick="hierarchyEditor.handleRemoveClick('+id+')" class="glyphicon glyphicon-remove gg-hierarchy-delete"></i>'
            + '</a>';
    };
    var createChild = function (content) {
        return '<div class="list-group">'
            + content
            + '</div>';
    };
};

function HierarchyObject() {
    this.id = "";
    this.name = "";
    this.item = null;
    this.parent = null;
    this.childList = [];
    this.nextObject = null;
    this.prevObject = null;

}