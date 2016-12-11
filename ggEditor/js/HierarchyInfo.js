/**
 * Created by knightofk9 on 11/21/2016.
 */



var hierarchyList = new function(){
    this.hierarchy = null;
    this.hierarchyIdDict = null;
    var that = this;
    var init = function(){
        // my.hierarchy = new HierarchyObject();
        // that.hierarchyIdDict = {};
    };
    this.reset = function(){
        hierarchyId = 0;
        my.hierarchyIdCount = 0;
        my.hierarchyIdDict = {};
        my.hierarchy = new HierarchyObject();
    };
    init();
};
