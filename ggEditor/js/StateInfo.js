/**
 * Created by Knight of k9 on 15/11/2016.
 */
function StateInfo(){
    var statePanel = $("#gg-state-info");
    var navTab = $("#gg-state-info-nav-tab");
    var useQuadTree = $("#gg-state-info-enable-quad-tree");
    this.setActive = function(isActive){
        if(isActive){
            statePanel.css("display","block");
            navTab.addClass("active");
        }else{
            statePanel.css("display","none");
            navTab.removeClass("active");
        }
    };
    this.isUsedQuadTree = function(){
        return useQuadTree.is(":checked");
    }
}