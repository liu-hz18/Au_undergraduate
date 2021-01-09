import getWrapper from "./utils"
import "@/mock/index"

import MessageBlock from '@/components/MessageBlock.vue'

describe('MessageBox.vue', () => {

  var passedProps = {
    title:"title1",
    content:"content",
    user:"user"
  }
  const wrapper = getWrapper(MessageBlock,passedProps)
  it('renders props when passed', () => {

    expect(wrapper.vm.$props.title).toBe(passedProps.title)
    expect(wrapper.findAll(".messageblock-datetime").length).toBe(1)
    expect(wrapper.findAll(".messageblock-user").length).toBe(1)
    expect(wrapper.findAll(".messageblock-user").at(0).text()).toBe(passedProps.user)
    expect(wrapper.findAll(".messageblock-content").length).toBe(1)
    expect(wrapper.findAll(".messageblock-content").at(0).text()).toBe(passedProps.content)

    console.log(wrapper.text())
  })
})
