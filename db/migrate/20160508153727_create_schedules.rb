class CreateSchedules < ActiveRecord::Migration
  def change
    create_table :schedules do |t|
      t.string :name
      t.text :description
      t.references :group, index: true, foreign_key: true
      t.string :cron
      t.int :duration_mins

      t.timestamps null: false
    end
  end
end
