/**
 * Created by Phan on 12/10/2016.
 */
function ObjectInfo(){
    var objectInfoPanel = $("#gg-object-info");
    var navTab = $("#gg-object-info-nav-tab");
    var objectInfoX = $("#gg-object-info-x");
    var objectInfoY = $("#gg-object-info-y");
    this.setActive = function(isActive){
        if(isActive){
            objectInfoPanel.css("display","block");
            navTab.addClass("active");
        }else{
            objectInfoPanel.css("display","none");
            navTab.removeClass("active");
        }
    };
}