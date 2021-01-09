import {mount,createLocalVue} from '@vue/test-utils'
import ElementUI from 'element-ui';

const localVue = createLocalVue()
localVue.use(ElementUI)
//require("@/mock/index")

let getWrapper = function(component,propsData){
    return mount(component, {
        localVue,
        propsData:propsData
    })
}
export default getWrapper