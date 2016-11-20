/**
 * Created by knightofk9 on 11/20/2016.
 */
var ObjectList = function(){
    var panel = $("#gg-tool-object-list");
    var navTab = $("#gg-tool-object-list-nav-tab");
    var that = this;
    //<li role="presentation" ><a role="menuitem" tabindex="-1" href="#" >Map 1</a></li>
    var objectSelect = $("#gg-object-tile");
    var charSelect = $("#gg-object-character");
    var tileSelect = $("#gg-object-tile");
    this.setActive = function(isActive){
        if(isActive){
            panel.css("display","block");
            navTab.addClass("active");
        }else{
            panel.css("display","none");
            navTab.removeClass("active");
        }

    };
    var init = function(){
        objectSelect.css("display","none");
        charSelect.css("display","none");
        tileSelect.css("display","none");
    };
    init();
};